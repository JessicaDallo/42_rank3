/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:06:12 by sheila            #+#    #+#             */
/*   Updated: 2024/12/02 17:38:23 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"


int	check_execpath(t_minishell *mshell, char *path)
{
	if(!path || path == NULL)
	{
		error_msg(mshell->commands->cmd, "Command not found");
		return(mshell->e_code = 127);
	}
	else
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
	}
	return(0);
}

char	*get_execpath(t_cmd *token)
{
	char	**paths;
	char	*tmp_path;
	int		i;
    char    *path;
	
	tmp_path = getenv("PATH");
	paths = ft_split(tmp_path, ':');
	if(!paths)
		return(NULL);
	i = -1;
	while(paths[++i])
	{
		path = ft_strjoin((ft_strjoin(paths[i], "/")), token->cmd);
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

void	run_execve(t_minishell *mshell, t_cmd *token)
{
	char	*exec_path;
	pid_t	pid;
	
	pid = creat_pid(mshell);
	if(pid == 0)
	{
		if(!token->input)
			return;
		if(!token->input[0])
			return;
		exec_path = get_execpath(token);
		if(execve(exec_path, token->input, mshell->envp))
		{
			check_execpath(mshell, exec_path);
			//mshell->e_code = 127;
			//clear_mshell(mshell);
		}
	}
	waitpid(pid, &mshell->e_code, 0);
	mshell->e_code = WEXITSTATUS(mshell->e_code);
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


/*void	run_execve(t_minishell *mshell, t_cmd *token)
{
	char	*executable;
	pid_t	pid;
	
	pid = creat_pid(mshell);
	if(pid == 0)
	{
		if(!token->input)
			return;
		if(!token->input[0])
			return;
		executable = get_execpath(token);
		//printf("\nPATH:%s\n ARGV:%s, %s.\n", executable, token->input[0], token->input[1]);
		//int i = 0;
		//while(mshell->envp[i])
        //	printf("\n\n%s\n", mshell->envp[i++]);
		//execve(executable, token->input, mshell->envp);
		if(execve(executable, token->input, mshell->envp))
		{
			//error_msg(token->cmd, "Command not found");
			check_execpath(mshell, executable);
			//mshell->e_code = 127;
			//clear_mshell(mshell);
		}
	}
	waitpid(pid, &mshell->e_code, 0);
	mshell->e_code = WEXITSTATUS(mshell->e_code);
	return;
}*/