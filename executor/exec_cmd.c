/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:25:14 by sheila            #+#    #+#             */
/*   Updated: 2025/01/03 00:31:52 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

pid_t	creat_pid(t_minishell *mshell)
{
	pid_t	child;
	
	child = fork();
	if(child < 0)
	{
		perror_msg("ERROR", "fork");
		mshell->e_code = 127;
	}
	return(child);	
}

void	run_cmd(t_minishell *mshell, t_cmd *cmd, int *prev_fd)
{
	signal(SIGINT, ft_sigint);
	//mshell->e_code = 0;
	if (*prev_fd != -1)
		redir_fds(*prev_fd, STDIN_FILENO);
	if (cmd->next)
		redir_fds(cmd->fd[1], STDOUT_FILENO);
	if(handle_redir(&(cmd->tokens)))
	{
		if (cmd->fd[0] != -1)
			close(cmd->fd[0]);
		if (!is_builtin(mshell, cmd))
				run_execve(mshell, cmd->tokens);
	}
	else
	{
		if (cmd->fd[0] != -1)
			close(cmd->fd[0]);
	}
	//printf("exit code cmd: %i\n", mshell->e_code);
	exit(mshell->e_code);
}

void handle_exec(t_minishell *mshell)
{
	int		initial_fds[2];

	save_original_fds(initial_fds);
	create_pipes(mshell->commands);
	if (mshell->commands && !mshell->commands->next)
	{
		if (has_heredoc(mshell, &mshell->commands->tokens))
		{
			if (mshell->e_code == 0)
				redir_fds(mshell->heredoc_fd, STDIN_FILENO);
		}
		//printf("handle_exec_entrou\n");
		if(handle_redir(&(mshell->commands->tokens)))
		{
			if(!is_builtin(mshell, mshell->commands))
				run_execve(mshell, mshell->commands->tokens);
		}
	}
	else
		exec_cmd(mshell);
	close_pipes(mshell->commands);
	recover_original_fds(initial_fds);
	close(initial_fds[0]);
	close(initial_fds[1]);
	//printf("handle_exec_saiu\n");
	return;
}


void exec_cmd(t_minishell *mshell)
{
	t_cmd   *cmd;
	pid_t   pid;
	int     prev_fd;

	cmd = mshell->commands;
	prev_fd = -1;
	while (cmd)
	{
		signal(SIGINT, ft_sigint);
		if (cmd->tokens && has_heredoc(mshell, &(cmd->tokens)))
		{
			if (mshell->e_code == 130)
				return;
			prev_fd = mshell->heredoc_fd;
		}
		pid = creat_pid(mshell);
		if (pid == 0)
			run_cmd(mshell, cmd, &prev_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(cmd->fd[1]);
		prev_fd = cmd->fd[0];
		waitpid(pid, &mshell->e_code, 0);
		check_exit_status(mshell);
		if (mshell->e_code != 0)
			return;
		cmd = cmd->next;
	}
}

/*void handle_exec(t_minishell *mshell)
{
	t_cmd	*cmd;
	int		initial_fds[2];

	cmd = mshell->commands;
	save_original_fds(initial_fds);
	create_pipes(cmd);
	if (cmd && !cmd->next)
	{
		if (has_heredoc(mshell, &cmd->tokens))
		{
			//if(mshell->e_code == 130)
			//	return;
			if (mshell->e_code == 0)
				redir_fds(mshell->heredoc_fd, STDIN_FILENO);
		}
		if(handle_redir(&(cmd->tokens)))
		{
			if(!is_builtin(mshell, cmd))
				run_execve(mshell, cmd->tokens);
		}
	}
	else
		exec_cmd(mshell);
	close_pipes(cmd);
	recover_original_fds(initial_fds);
	close(initial_fds[0]);
	close(initial_fds[1]);
	return;
}*/