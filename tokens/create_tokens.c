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

// int	get_type(char *cmd)
// {
// 	if(ft_strcmp (cmd, "|") == 0)
// 		return PIPE;
// 	else if(ft_strcmp(cmd, ">") == 0)
// 		return OUTPUT_REDIR;
// 	else if (ft_strcmp(cmd, ">>") == 0)
// 		return APPEND_REDIR;
// 	else if(ft_strcmp(cmd, "<") == 0)
// 		return INPUT_REDIR;
// 	else if(ft_strcmp(cmd, "<<") == 0)
// 		return HEREDOC;
// 	else 
// 		return CMD;
// }

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
//old version
// t_token	*add_token(t_token **token, char *arg, token_type type)
// {
// 	t_token	*temp;
// 	t_token	*new_token;

// 	new_token = create_token(arg, type);
// 	//while(*token->next != NULL)
// 	//	*token = token->next;
// 	if (!new_token)
// 		return (NULL);
// 	if (*token == NULL)
// 	{
// 		*token = new_token;
// 		return (*token);
// 	}
// 	temp = *token;
// 	while (temp->next != NULL)
// 		temp = temp->next;
// 	temp->next = new_token;
// 	return (temp);
// }
//tentar colocar  o token dentrodo cmd correto 
void	*add_token(t_cmd **cmd, char *arg, token_type type)
{
	t_cmd	*temp;
	t_token	*new_token;

	new_token = create_token(arg, type);
	// while(*temp->next != NULL)
	// 	*temp = temp->next;
	if (!new_token)
		return (NULL);
	if ((*cmd)->token == NULL)
	{
		(*cmd)->token = new_token;
		return NULL;
	}
	temp = *cmd;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next->token = new_token;
	return (temp);
}


// void	add_cmd(t_cmd **cmd, t_token **token)
// {
// 	t_cmd	*new_cmd;
// 	t_cmd	*temp;

// 	new_cmd = calloc(1, sizeof(t_cmd));
// 	new_cmd->token = *token;
// 	new_cmd->next = NULL;
// 	if (!new_cmd)
// 		return ;
// 	if(*cmd == NULL)
// 	{
// 		*cmd = new_cmd;
// 		return ;
// 	}
// 	temp = *cmd;
// 	while(temp->next !=  NULL)
// 		temp = temp->next;
// 	temp->next = new_cmd;
// }

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
