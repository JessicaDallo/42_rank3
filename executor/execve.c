/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:06:12 by sheila            #+#    #+#             */
/*   Updated: 2025/01/02 22:59:25 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	execpath_error(t_minishell *mshell, char *path)
{
	if(ft_strchr(path, '/') || path[0] == '.')
	{
		if (access(path, F_OK) < 0)
		{
			error_msg(path, "No such file or directory", 127);
			return(mshell->e_code = 127);
		}
		else if (access(path, X_OK) == 0)
		{
			error_msg(path, "Is a directory", 126);
			return(mshell->e_code = 126);
		}
		else
		{
			error_msg(path, "Permission denied", 126);
			return(mshell->e_code = 126);
		}
	}
	return(mshell->e_code);
}

int	check_execpath(t_minishell *mshell, char *path)
{
	if(!path || path == NULL)
	{
		error_msg(mshell->commands->tokens->input, "command not found", 127);
		return(mshell->e_code = 127);
	}
	else
		return(execpath_error(mshell, path));
}

char	*get_execpath(t_minishell *mshell, char *cmd_name)
{
	char	**paths;
	char	*tmp_path;
	char	*path;
	int		i;
	
	if(ft_strchr("/.", cmd_name[0]))
		return(ft_strdup(cmd_name));
	tmp_path = get_value(mshell, "PATH");
	if(tmp_path)
		paths = ft_split(tmp_path, ':');
	if(!tmp_path || !paths)
		return(NULL);
	i = -1;
	while(paths[++i])
	{
		path = ft_strjoin((ft_strjoin(paths[i], "/")), cmd_name);
		if(access(path, F_OK) == 0)
		{
			free_array(paths);
			return(ft_strdup(path));
		}
		free(path);
	}
	free_array(paths);
	return(NULL);
}

void	check_exit_status(t_minishell *mshell)
{
	if(WIFEXITED(mshell->e_code))
		mshell->e_code = WEXITSTATUS(mshell->e_code);
	else if (WIFSIGNALED(mshell->e_code)) 
		mshell->e_code = 128 + WTERMSIG(mshell->e_code);
	//printf("exit_code: %d\n", mshell->e_code);
	if(mshell->e_code != 0)
	{
		free_cmd(mshell->commands);
		mshell->commands = NULL;
	}
}

void	run_execve(t_minishell *mshell, t_token *token)
{
	char	*executable;
	char	**args;
	pid_t	pid;

	if(!token || !token->input)
		return;
	pid = creat_pid(mshell);
	args = convert_args(mshell, token);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	if(pid == 0)
	{
		signal(SIGINT, ft_sigint);
		 if(!args || !args[0])
		 	return;
		//if(!args || !args[0] || !args[0][0])
		//	error_msg("", "command '' not found", 127);
		executable = get_execpath(mshell, args[0]);
		if(execve(executable, args, mshell->envp))
			check_execpath(mshell, executable);
		exit(mshell->e_code);
	}
	waitpid(pid, &mshell->e_code, 0);
	check_exit_status(mshell);
	free_array(args);
	return;
}
