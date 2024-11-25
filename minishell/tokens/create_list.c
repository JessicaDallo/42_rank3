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

#include "../includes/include_builtins.h"

bool is_delimiter(char *arg)
{
	if(ft_strcmp(arg, "|") == 0 || ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<") == 0 || !arg)
		return (true);
	return (false);
}

int len_array(char **arg)
{
	int i = 0;
	while(!is_delimiter(arg[i]))
		i++;
	return (i);
}

void  handle_value(char **arg, t_token **token)
{
	while(ft_strcmp(*arg, "export") == 1)
		arg++;
	arg++;
	printf("%s -> handle value\n", *arg);
	int len = len_array(arg);
	printf("%d LEN HANDLE\n",len);
	if ((*token)->value == NULL)
		(*token)->value = ft_calloc(sizeof(char *), len);
}


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
