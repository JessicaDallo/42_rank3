/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:10:05 by sheila            #+#    #+#             */
/*   Updated: 2025/01/04 23:00:16 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *cmd, char *str, int e_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_e_code = e_code;
}

void	perror_msg(char *cmd, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(str);
	g_e_code = errno;
}

t_minishell	*minishell(t_minishell *mshell)
{
	static t_minishell	*minishell = NULL;

	if(mshell)
		minishell = mshell;

	return (minishell);
}

void	close_fds(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	free_mshell(t_minishell *mshell)
{
	if (!mshell)
		return ;
	if (mshell->env)
		free_envlist(mshell->env);
	if (mshell->commands)
		free_cmd(mshell->commands);
	if (mshell->envp)
		free_array(mshell->envp);
	close(mshell->heredoc_fd);
	close(mshell->initial_fds[0]);
	close(mshell->initial_fds[1]);
	close_fds();
}

