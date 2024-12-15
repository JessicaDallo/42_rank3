// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   create_tokens.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/27 09:49:03 by jesilva-          #+#    #+#             */
// /*   Updated: 2024/11/27 09:49:10 by jesilva-         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/include_builtins.h"

t_token	*create_token(char *arg, token_type type)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->input = ft_strdup(arg);
	new_token->next = NULL;

	return (new_token);
}

static void	add_end_token(t_cmd *temp, t_token *new_token)
{
	t_token	*tmp_token;

	while (temp->next != NULL)
				temp = temp->next;
	tmp_token = temp->token;
	while (tmp_token->next != NULL)
		tmp_token = tmp_token->next;
	tmp_token->next = new_token;
}

void	*add_token(t_cmd **cmd, char *arg, token_type type, bool teste)
{
	t_cmd	*temp;
	t_token	*new_token;

	new_token = create_token(arg, type);
	if (!new_token)
		return (NULL);
	if ((*cmd)->token == NULL)
	{
		(*cmd)->token = new_token;
		return NULL;
	}
	temp = *cmd;
	if(teste == true)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->token = new_token;
		return (temp);
	}
	else
		add_end_token(temp, new_token);
	return (temp);
}

void	add_cmd(t_cmd **cmd)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_cmd->token = NULL;
	new_cmd->next = NULL;
	if (!new_cmd)
		return ;
	if(*cmd == NULL)
	{
		*cmd = new_cmd;
		return ;
	}
	temp = *cmd;
	while(temp->next !=  NULL)
		temp = temp->next;
	temp->next = new_cmd;
}

void free_token(t_token *token) {
    if (token) {
        if (token->input) // Liberar a string alocada
            free(token->input);
        free(token); // Liberar o próprio nó
    }
}


void free_token_list(t_token *head) {
    t_token *temp;

    while (head) {
        temp = head->next;
        free_token(head); // Libera o nó atual
        head = temp;      // Move para o próximo nó
    }
}

void free_cmd(t_cmd *cmd) {
    t_cmd *temp;

    while (cmd) {
        temp = cmd->next;
        if (cmd->token) // Libera a lista de tokens associada
            free_token_list(cmd->token);
        free(cmd); // Libera o próprio nó de comando
        cmd = temp;
    }
}
