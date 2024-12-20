/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2024/12/17 23:19:10 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

// void	creat_pipes(t_cmd *cmd)
// {

// }

/*void exec_cmd(t_minishell *mshell)
{
    t_cmd *cmd = mshell->commands;
    pid_t pid;
    int prev_fd = -1;

    while (cmd)
    {
        if (!cmd->tokens || !cmd->tokens->input)
        {
            clear_mshell(mshell);
            return;
        }

        // Criar o pipe para o próximo comando, se necessário
        if (cmd->next && pipe(cmd->fd) == -1)
        {
            perror("Pipe error");
            return;
        }

        pid = creat_pid(mshell);
        if (pid == 0) // Processo filho
        {
            // Configurar entrada (heredoc ou input file)
            has_heredoc(mshell, &(cmd->tokens));// Configura o stdin para o heredoc
            handle_redir(&(cmd->tokens)); // Configura redirecionamentos (<, >, >>)

            // Configurar saída (pipe para o próximo comando, se existir)
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // Redirecionar saída, se necessário
            if (cmd->next)
            {
                dup2(cmd->fd[1], STDOUT_FILENO);
                close(cmd->fd[1]);
            }

            // Fechar descritores desnecessários
            if (cmd->fd[0] != -1)
                close(cmd->fd[0]);

            // Executar comando
            if (is_builtin(mshell, cmd))
                return;
            else
                run_execve(mshell, cmd->tokens);  
            exit(mshell->e_code);
        }
        if (cmd->fd[0] != -1)
            close(cmd->fd[0]);
        if (cmd->next)
            close(cmd->fd[1]);
        waitpid(pid, &mshell->e_code, 0);
	    //f(WIFEXITED(mshell->e_code))
		    //mshell->e_code = WEXITSTATUS(mshell->e_code);
        // Fechar descritores não mais usados
        // Atualizar para o próximo comando
        cmd = cmd->next;
    }
    while (waitpid(-1, &mshell->e_code, 0) > 0)
        ;
    if (WIFEXITED(mshell->e_code))
        mshell->e_code = WEXITSTATUS(mshell->e_code);
}*/

/*void exec_cmd(t_minishell *mshell)
{
    t_cmd *cmd = mshell->commands;
    pid_t pid;

    while (cmd)
    {
        if (!cmd->tokens || !cmd->tokens->input)
        {
            clear_mshell(mshell);
            return;
        }

        // Criar o pipe para o próximo comando, se necessário
        if (cmd->next && pipe(cmd->fd) == -1)
        {
            perror("Pipe error");
            return;
        }

        pid = creat_pid(mshell);
        if (pid == 0) // Processo filho
        {
            // Configurar entrada (heredoc ou input file)
            has_heredoc(mshell, &(cmd->tokens));// Configura o stdin para o heredoc
            handle_redir(&(cmd->tokens)); // Configura redirecionamentos (<, >, >>)

            // Configurar saída (pipe para o próximo comando, se existir)
            if (cmd->next)
                dup2(cmd->fd[1], STDOUT_FILENO);

            // Fechar descritores do pipe
            if (cmd->fd[0] != -1)
                close(cmd->fd[0]);
            if (cmd->fd[1] != -1)
                close(cmd->fd[1]);

            // Executar comando
            if (is_builtin(mshell, cmd))
                return;
            else
                run_execve(mshell, cmd->tokens);  
            //exit(mshell->e_code);
        }
        waitpid(pid, &mshell->e_code, 0);
	    if(WIFEXITED(mshell->e_code))
		    mshell->e_code = WEXITSTATUS(mshell->e_code);
        // Fechar descritores não mais usados
        if (cmd->fd[1] != -1)
            close(cmd->fd[1]);

        // Atualizar para o próximo comando
        cmd = cmd->next;
    }
}*/