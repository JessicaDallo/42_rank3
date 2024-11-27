/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:49:03 by jesilva-          #+#    #+#             */
/*   Updated: 2024/11/27 09:49:10 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include_builtins.h"

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
	new_token->type = type;
	new_token->name = ft_strdup(arg);
	new_token->value = NULL;
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
