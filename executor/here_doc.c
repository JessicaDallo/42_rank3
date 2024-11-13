/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2024/11/13 18:42:04 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/include_builtins.h"

//void	handle_pipe(t_minishell *mshell, char **line)
//{
	
//}

/*int	creat_pipe(void)
{
	int	fd[2];
	pid_t	pid;

	pid = fork();
	if(fork < 0)
		error_msg("fork", "get_pid");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd, STDOUT_FILENO);
		close(fd[1]);
		//execve();
	}
	else
	{
		close(fd[1]);
		dup2(fd, STDIN_FILENO);
		close(fd[0]);
		//execve();
	}
	waitpid(pid, NULL, 0);
	return(0);
}*/
