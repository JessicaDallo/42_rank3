/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:06:12 by sheila            #+#    #+#             */
/*   Updated: 2025/01/07 19:44:45 by sheila           ###   ########.fr       */
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

int	check_execpath(t_token *token, char *path)
{
	if (!path || path == NULL)
	{
		error_msg(token->input, "command not found", 127);
		return (g_e_code = 127);
	}
	else
		return (execpath_error(path));
}

char	*get_execpath(t_minishell *mshell, char *cmd_name)
{
	char	**paths;
	char	*tmp_path;
	char	*path;
	int		i;

	if (ft_strchr("/.", cmd_name[0]))
		return (ft_strdup(cmd_name));
	tmp_path = get_value(mshell, "PATH");
	if (tmp_path)
		paths = ft_split(tmp_path, ':');
	if (!tmp_path || !paths)
		return (NULL);
	i = -1;
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
	if (WIFEXITED(g_e_code))
		g_e_code = WEXITSTATUS(g_e_code);
	else if (WIFSIGNALED(g_e_code))
		g_e_code = 128 + WTERMSIG(g_e_code);
	if (g_e_code == 130)
	{
		free_cmd(mshell->commands);
		mshell->commands = NULL;
	}
}
// void	child_run_execve()
// {

// }

void	run_execve(t_minishell *mshell, t_token *token)
{
	char	*executable;
	char	**args;
	pid_t	pid;

	expand_args(mshell, token);
	//if (!token || !token->input || (!*token->input && !token->next)) resolver $EMPTY de outra forma
	if (!token || !token->input)
		return ;
	args = convert_args(mshell, token);
	if (!args || !args[0])
		return ;
	pid = creat_pid();
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		// if (!args || !args[0])
		// 	return ;
		executable = get_execpath(mshell, args[0]);
		if(!executable)
		{
			check_execpath(token, executable);
			free_array(args);
			clear_mshell(mshell);
		}
		if (execve(executable, args, mshell->envp))
			check_execpath(token, executable);
		free(executable);
		free_array(args);
		clear_mshell(mshell);
		//exit(mshell->e_code);
	}
	waitpid(pid, &g_e_code, 0);
	check_exit_status(mshell);
	free_array(args);
	return ;
}

/*void	run_execve(t_minishell *mshell, t_token *token)
{
	char	*executable;
	char	**args;
	pid_t	pid;

	expand_args(mshell, token);
	if (!token || !token->input)
		return ;
	args = convert_args(mshell, token);
	pid = creat_pid(mshell);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	if (pid == 0)
	{
		signal(SIGINT, ft_sigint);
		ft_putendl("entrei aqui 0");
		if (args && *args[0])
		{
			ft_putendl("entrei aqui 1");

		//executable = get_execpath(mshell, args[0]);
			if(!(executable = get_execpath(mshell, args[0])))
			{
				ft_putendl("entrei aqui 2");
				check_execpath(mshell, token, executable);
			}
			else
			{
				ft_putendl("entrei aqui 3");
				if(execve(executable, args, mshell->envp))
					check_execpath(mshell, token, executable);
			}
			ft_putendl("passei aqui 4");
			if(executable)
				free(executable);
			free_array(args);
		}
		ft_putendl("passei aqui 5");
		clear_mshell(mshell);
		exit(mshell->e_code);
	}
	waitpid(pid, &mshell->e_code, 0);
	check_exit_status(mshell);
	free_array(args);
	return ;
}*/
