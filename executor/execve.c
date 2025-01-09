/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:06:12 by sheila            #+#    #+#             */
/*   Updated: 2025/01/09 02:18:39 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execpath_error(char *path)
{
	if (ft_strchr(path, '/') || path[0] == '.')
	{
		if (access(path, F_OK) < 0)
		{
			error_msg(path, "No such file or directory", 127);
			return (g_e_code = 127);
		}
		else if (access(path, X_OK) == 0)
		{
			error_msg(path, "Is a directory", 126);
			return (g_e_code = 126);
		}
		else
		{
			error_msg(path, "Permission denied", 126);
			return (g_e_code = 126);
		}
	}
	return (g_e_code);
}

int	check_execpath(char *args, char *path)
{
	if (!path || path == NULL)
	{
		error_msg(args, "command not found", 127);
		return (g_e_code = 127);
	}
	else
		return (execpath_error(path));
}

char	*get_execpath(t_minishell *mshell, char *cmd_name, int i)
{
	char	**paths;
	char	*tmp_path;
	char	*path;

	if (ft_strchr("/.", cmd_name[0]))
		return (ft_strdup(cmd_name));
	tmp_path = get_value(mshell, "PATH");
	if (tmp_path)
		paths = ft_split(tmp_path, ':');
	if (!tmp_path || !paths)
		return (NULL);
	while (paths[++i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp_path, cmd_name);
		free(tmp_path);
		if (access(path, F_OK) == 0)
		{
			free_array(paths);
			return (ft_strdup(path));
		}
		free(path);
	}
	free_array(paths);
	return (NULL);
}

void	check_exit_status(t_minishell *mshell)
{
	(void)mshell;
	if (WIFEXITED(g_e_code))
		g_e_code = WEXITSTATUS(g_e_code);
	else if (WIFSIGNALED(g_e_code))
		g_e_code = 128 + WTERMSIG(g_e_code);
}

void	run_execve(t_minishell *mshell, t_token *token)
{
	char	**args;
	pid_t	pid;

	if (!token || !token->input)
		return ;
	args = convert_args(mshell, token);
	if (!args || !args[0])
		return ;
	pid = creat_pid();
	check_pid(token);
	if (pid == 0)
	{
		close_pipes(mshell->commands);
		check_execve(mshell, args);
		clear_mshell(mshell);
	}
	close_pipes(mshell->commands);
	waitpid(pid, &g_e_code, 0);
	check_exit_status(mshell);
	free_array(args);
	return ;
}
