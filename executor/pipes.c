/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2025/01/03 00:41:02 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	create_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;
	
	tmp = cmd;
	while (tmp)
	{
		if (tmp->next && pipe(tmp->fd) == -1)
		{
			perror_msg("pipe", "error to create pipe");
			return;
		}
		tmp = tmp->next;
	}
	return;
}

void	close_pipes(t_cmd *cmd)
{
	t_cmd   *tmp;
	
	if (!cmd)
		return;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->fd[0] != -1)
			close(tmp->fd[0]);
		else if (tmp->fd[1] != -1)
			close(tmp->fd[1]);
		tmp = tmp->next;
	}
}

void	redir_fds(int redir, int local)
{  
	if(redir < 0 || local < 0)
	{
		error_msg("fd", "No such file or directory", 1);
		return;
	}
	else if (dup2(redir, local) < 0)
	{
		perror_msg("dup2", "Error redirecting");
		close(redir);
		return;
	}
	close(redir);
}

void	save_original_fds(int initial_fds[2])
{
	initial_fds[0] = dup(STDIN_FILENO);
	initial_fds[1] = dup(STDOUT_FILENO);
}

void	recover_original_fds(int initial_fds[2])
{
	redir_fds(initial_fds[0], STDIN_FILENO);
	redir_fds(initial_fds[1], STDOUT_FILENO);
}
