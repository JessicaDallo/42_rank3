/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:45:53 by sheila            #+#    #+#             */
/*   Updated: 2025/01/04 23:00:49 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_token(t_token **tokens, t_token **current)
{
	t_token	*tmp;
	t_token	*prev;

	if (!tokens || !*tokens || !current || !*current)
		return ;
	tmp = *current;
	prev = NULL;
	if (tmp == *tokens)
		*tokens = tmp->next;
	else
	{
		prev = *tokens;
		while (prev && prev->next != tmp)
			prev = prev->next;
		if (prev)
			prev->next = tmp->next;
	}
	if (tmp->input)
		free(tmp->input);
	*current = tmp->next;
	free(tmp);
}

bool	check_redir(t_token *temp)
{
	bool	redir;

	redir = true;
	if (temp->type == INPUT_REDIR)
		redir = redir_input(temp->input);
	else if (temp->type == OUTPUT_REDIR)
		redir = redir_output(temp->input);
	else if (temp->type == APPEND_REDIR)
		redir = redir_append(temp->input);
	return (redir);
}

bool	handle_redir(t_token **tokens)
{
	t_token	*temp;
	bool	flag;

	if (!tokens || !*tokens)
		return (false);
	flag = true;
	temp = *tokens;
	while (temp)
	{
		if (temp->type == INPUT_REDIR || temp->type == OUTPUT_REDIR \
			|| temp->type == APPEND_REDIR)
		{
			flag = check_redir(temp);
			remove_token(tokens, &temp);
		}
		else
			temp = temp->next;
		if (!flag)
			break ;
	}
	return (flag);
}
