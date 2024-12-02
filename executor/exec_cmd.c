/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:25:14 by sheila            #+#    #+#             */
/*   Updated: 2024/12/01 16:28:49 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

/*void	exec_cmd(t_minishell *mshell, t_cmd *token)
{
        
	//if(is_builtin(mshell, token))
	//	return;
	//else
		executable(mshell, token);
	return;
}

void handle_pipes(t_minishell *mshell, t_cmd *cmd)
{
    int fds[2];
    //int fd_in = 0;
    pid_t pid;
    
    pipe(fds);
    pid = creat_pid(mshell); // Cria o pipe para conectar os comandos
    if (pid == 0)
    {
        //dup2(fd_in, STDIN_FILENO); // primeiro comando
        dup2(fds[1], STDOUT_FILENO); 
        close(fds[0]);
        //handle_redir(cmd->name, cmd->value);
        exec_cmd(mshell, cmd);
    }
    else
    {
        waitpid(pid, &mshell->e_code, 0);
        close(fds[1]); 
        //fd_in = fds[0];
    }
    cmd = cmd->next;
}

void	run_commands(t_minishell *mshell)
{
	t_cmd	*cmd;
	//t_redir	*redir;

	cmd = mshell->commands;
	while(cmd)
	{
		if (!cmd->next)
			exec_cmd(mshell, cmd);
		else if (cmd->next)
            handle_pipes(mshell, cmd);
		//else if (commands->type == OUTPUT_REDIR)
		//	//função
		//else if (commands->type == APPEND_REDIR)
		//	//função
		//else if (commands->type == INPUT_REDIR)
		//	//função
		//else if (commands->type == HEREDOC)
		//	//função
		cmd = cmd->next;
	}
}*/

