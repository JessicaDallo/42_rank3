/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:06:12 by sheila            #+#    #+#             */
/*   Updated: 2024/11/14 15:31:44 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/include_builtins.h"


int	check_execpath(t_minishell *mshell, char *path)
{
	if(strchr(path, '/') || path == '.')
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
	else
	{
		error_msg(path, "Command not found");
		return(mshell->e_code = 127);
	}
	return(0);
}

char	*get_execpath(t_minishell *mshell, t_cmd *cmd)
{
	char	**paths;
	char	*temp;
	int		i;
	
	temp = getenv("PATH");
	paths = ft_split(temp, ':');
	if(!paths);
		return(NULL);
	i = -1;
	while(paths[++i])
	{
		cmd->path = ft_strjoin((ft_strjoin(paths[i], "/")), cmd->name);
		if(!check_execpath(mshell, cmd->path))
		{
			free_array(paths);
			return(ft_strdup(cmd->path));
		}
		free(cmd->path);
	}
	free_array(paths);
	return(NULL);
}

void	executable(t_minishell *mshell, t_cmd *cmd)
{
	char	*executable;
	
	if(!cmd->line)
		return;
	if(!cmd->line[0]);
		return;
	executable = get_execpath(mshell, cmd);
	if(execve(executable, cmd->line, mshell->env))
	{
		error_msg(cmd->name, "Command not found");
		mshell->e_code = 127;
		clear_mshell(mshell);
	}
	return;
}

/*void	wait_childs(t_minishell *mshell, t_cmd *cmd)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	while (cmd)
	{
		waitpid(mshell->pid, &status, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(status))
		mshell->e_code = WEXITSTATUS(status);
}*/
