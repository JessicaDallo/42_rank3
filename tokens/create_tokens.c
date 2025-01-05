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

#include "../includes/minishell.h"

int	get_type(char *cmd, bool new_cmd)
{
	if (new_cmd == true && !is_delimiter(cmd))
		return (CMD);
	else if (ft_strcmp(cmd, ">") == 0)
		return (OUTPUT_REDIR);
	else if (ft_strcmp(cmd, ">>") == 0)
		return (APPEND_REDIR);
	else if (ft_strcmp(cmd, "<") == 0)
		return (INPUT_REDIR);
	else if (ft_strcmp(cmd, "<<") == 0)
		return (HEREDOC);
	else
		return (ARG);
}

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
	tmp_token = temp->tokens;
	while (tmp_token->next != NULL)
		tmp_token = tmp_token->next;
	tmp_token->next = new_token;
}

void	*add_token(t_cmd **cmd, char *arg, token_type type, bool new_cmd)
{
	t_cmd	*temp;
	t_token	*new_token;

	new_token = create_token(arg, type);
	if (!new_token)
		return (NULL);
	if ((*cmd)->tokens == NULL)
	{
		(*cmd)->tokens = new_token;
		return (NULL);
	}
	temp = *cmd;
	if (new_cmd == true)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->tokens = new_token;
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
	new_cmd->tokens = NULL;
	new_cmd->next = NULL;
	new_cmd->fd[0] = -1;
	new_cmd->fd[1] = -1;
	if (!new_cmd)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new_cmd;
		return ;
	}
	temp = *cmd;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_cmd;
}
