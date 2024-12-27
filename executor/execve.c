/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:06:12 by sheila            #+#    #+#             */
/*   Updated: 2024/12/23 15:30:35 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	execpath_error(t_minishell *mshell, char *path)
{
	if(ft_strchr(path, '/') || path[0] == '.')
	{
		if (access(path, F_OK) < 0)
		{
			error_msg(path, "No such file or directory");
			return(mshell->e_code = 127);
		}
		else if (access(path, X_OK) == 0)
		{
			error_msg(path, "Is a directory");
			return(mshell->e_code = 126);
		}
		else
		{
			error_msg(path, "Permission denied");
			return(mshell->e_code = 126);
		}
	}
	return(mshell->e_code);
}

int	check_execpath(t_minishell *mshell, char *path)
{
	if(!path || path == NULL)
	{
		error_msg(mshell->commands->tokens->input, "Command not found");
		return(mshell->e_code = 127);
	}
	else
		return(execpath_error(mshell, path));
	//return(0);
}

char	*get_execpath(char *cmd_name)
{
	char	**paths;
	char	*tmp_path;
	int		i;
    char    *path;
	
	if(ft_strchr("/.", cmd_name[0]))
		return(ft_strdup(cmd_name));
	tmp_path = getenv("PATH");
	paths = ft_split(tmp_path, ':');
	if(!paths)
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

void	run_execve(t_minishell *mshell, t_token *token)
{
	char	*executable;
	char	**args;
	pid_t	pid;
	
	if(!token->input)
		return;
	pid = creat_pid(mshell);
	args = convert_args(token);
	signal(SIGINT, SIG_IGN); // Ignorar SIGINT no processo principal
	signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT no processo principal
	if(pid == 0)
	{
		signal(SIGINT, ft_sigint);
		if(!args || !args[0])
			return;
		executable = get_execpath(args[0]);
		if(execve(executable, args, mshell->envp))
			check_execpath(mshell, executable);
		exit(mshell->e_code);
	}
	waitpid(pid, &mshell->e_code, 0);
	if(WIFEXITED(mshell->e_code)) // Verifica se o processo filho terminou normalmente (sem sinais)
		mshell->e_code = WEXITSTATUS(mshell->e_code); //extrai o código de saída (return code) do processo filho
	free_array(args);
	return;
}
