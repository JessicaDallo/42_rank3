/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2025/01/09 01:51:03 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->next && pipe(cmd->fd) == -1)
		{
			perror_msg("pipe", "error to create pipe");
			return ;
		}
		cmd = cmd->next;
	}
	return ;
}

void	close_pipes(t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->fd[0] != -1)
			close(cmd->fd[0]);
		if (cmd->fd[1] != -1)
			close(cmd->fd[1]);
		cmd = cmd->next;
	}
}

void	redir_fds(int redir, int local)
{
	if (redir < 0 || local < 0)
	{
		error_msg("fd", "No such file or directory", 1);
		return ;
	}
	else if (dup2(redir, local) < 0)
	{
		perror_msg("dup2", "Error redirecting");
		close(redir);
		return ;
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
	close(initial_fds[0]);
	close(initial_fds[1]);
}
