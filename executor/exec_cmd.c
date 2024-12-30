/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:25:14 by sheila            #+#    #+#             */
/*   Updated: 2024/12/29 14:30:19 by sheila           ###   ########.fr       */
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

int    check_cmd(t_minishell *mshell, t_cmd **cmd, int *prev_fd)
{
	if ((*cmd)->tokens && has_heredoc(mshell, &((*cmd)->tokens)))
		*prev_fd = mshell->heredoc_fd;
	if (is_builtin(*cmd) && !(*cmd)->next)
	{
		run_builtin(mshell, *cmd);
		*cmd = (*cmd)->next;
		return (1);
	}
	return (0);
}

void    run_cmd(t_minishell *mshell, t_cmd *cmd, int *prev_fd)
{
	if (*prev_fd != -1)
		redir_fds(*prev_fd, STDIN_FILENO);
	if (cmd->next)
		redir_fds(cmd->fd[1], STDOUT_FILENO);
	handle_redir(&(cmd->tokens));
	if (cmd->fd[0] != -1)
		close(cmd->fd[0]);
	if (is_builtin(cmd))
	{
		run_builtin(mshell, cmd);
		exit(mshell->e_code);
	}
	else
		run_execve(mshell, cmd->tokens);
	exit(mshell->e_code);
}

void exec_cmd(t_minishell *mshell)
{
	t_cmd   *cmd;
	pid_t   pid;
	int     prev_fd;

	cmd = mshell->commands;
	prev_fd = -1;
	create_pipes(cmd);
	while (cmd)
	{
		if (check_cmd(mshell, &cmd, &prev_fd))
			continue;
		signal(SIGINT, ft_sigint);
		pid = creat_pid(mshell);
		if (pid == 0)
			run_cmd(mshell, cmd, &prev_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(cmd->fd[1]);
		prev_fd = cmd->fd[0];
		waitpid(pid, &mshell->e_code, 0);
		if (WIFEXITED(mshell->e_code))
			mshell->e_code = WEXITSTATUS(mshell->e_code);
		cmd = cmd->next;
	}
}

// void exec_cmd(t_minishell *mshell)
// {
//     t_cmd   *cmd;
//     pid_t   pid;
//     int     prev_fd;

//     cmd = mshell->commands;
//     prev_fd = -1;
//     create_pipes(cmd);
//     while (cmd)
//     {
//         if (cmd->tokens && has_heredoc(mshell, &(cmd->tokens)))
//             prev_fd = mshell->heredoc_fd;
//         if (is_builtin(cmd) && !cmd->next)
//         {
//             run_builtin(mshell, cmd);
//             cmd = cmd->next;
//             continue;
//         }
//         signal(SIGINT, ft_sigint);
//         pid = creat_pid(mshell);
//         if (pid == 0)
//             run_cmd(mshell, cmd, &prev_fd);
//         if (prev_fd != -1)
//             close(prev_fd);
//         if (cmd->next)
//             close(cmd->fd[1]);
//         prev_fd = cmd->fd[0];
//         waitpid(pid, &mshell->e_code, 0);
//         if (WIFEXITED(mshell->e_code))
//             mshell->e_code = WEXITSTATUS(mshell->e_code);
//         cmd = cmd->next;
//     }
// }

/*void    run_cmd(t_minishell *mshell, t_cmd *cmd, int *prev_fd)
{
	if (*prev_fd != -1)
		redir_fds(*prev_fd, STDIN_FILENO);
	if (cmd->next)
		redir_fds(cmd->fd[1], STDOUT_FILENO);
	handle_redir(&(cmd->tokens));
	if (cmd->fd[0] != -1)
		close(cmd->fd[0]);
	if (is_builtin(mshell, cmd))
		exit(mshell->e_code);
	else
		run_execve(mshell, cmd->tokens);
	exit(mshell->e_code);
}

void exec_cmd(t_minishell *mshell)
{
	t_cmd   *cmd;
	pid_t   pid;
	int     prev_fd;

	cmd = mshell->commands;
	prev_fd = -1;
	create_pipes(cmd);
	while (cmd)
	{
		if (cmd->tokens && has_heredoc(mshell, &(cmd->tokens)))
			prev_fd = mshell->heredoc_fd;
		pid = creat_pid(mshell);
		if (pid == 0)
			run_cmd(mshell, cmd, &prev_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(cmd->fd[1]);
		prev_fd = cmd->fd[0];
		waitpid(pid, &mshell->e_code, 0);
		if (WIFEXITED(mshell->e_code))
			mshell->e_code = WEXITSTATUS(mshell->e_code);
		cmd = cmd->next;
	}
}*/
