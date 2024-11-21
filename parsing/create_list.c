/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:33:19 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 15:33:19 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	get_type(char *cmd)
{
	if(ft_strcmp (cmd, "|") == 0)
		return PIPE;
	else if(ft_strcmp(cmd, ">") == 0)
		return OUTPUT_REDIR;
	else if (ft_strcmp(cmd, ">>") == 0)
		return APPEND_REDIR;
	else if(ft_strcmp(cmd, "<") == 0)
		return INPUT_REDIR;
	else if(ft_strcmp(cmd, "<<") == 0)
		return HEREDOC;
	else 
		return CMD;
}

t_token *create_token(char *arg, token_type type)
{
	t_token *new_token;

	new_token = calloc(1, sizeof(t_token));
	if(!new_token)
		return (NULL);
	//type = get_type(arg, flg_red);
	new_token->type = type;
	new_token->value = ft_strdup(arg);
	new_token->next = NULL;

	return (new_token);
}

void add_token(t_token **token, char *arg, token_type type)
{
	t_token *temp;
	t_token *new_token;

	new_token = create_token(arg, type);
	if(!new_token)
		return ;
	if(*token == NULL)
	{
		*token = new_token;
		return ;
	}
	temp = *token;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = new_token;
}

// void free_token(t_token *token)
// {
// 	t_token *temp;

// 	if(!token)
// 		return ;
// 	while(temp)
// 	{
// 		temp = head;
// 		head = head->next;
// 		free(temp->value);
// 		free(temp);
// 	}
// }