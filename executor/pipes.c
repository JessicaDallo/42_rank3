/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2024/12/20 23:45:49 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

// void	creat_pipes(t_cmd *cmd)
// {

// }


/*static void	save_original_fds(int original_fds[2])
{
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
}

void	redirect_fd(int fd_to_redirect, int fd_location)
{
	dup2(fd_to_redirect, fd_location);
	close(fd_to_redirect);
}

void	redirect_fds(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		redirect_fd(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		redirect_fd(fd_out, STDOUT_FILENO);
}

static void	restore_original_fds(int original_fds[2])
{
	redirect_fd(original_fds[0], STDIN_FILENO);
	redirect_fd(original_fds[1], STDOUT_FILENO);
}


void exec_cmd(t_minishell *mshell)
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

void exec_cmd(t_minishell *mshell)
{
    t_cmd *cmd = mshell->commands;
    pid_t pid;
    int prev_fd = -1;

    while (cmd)
    {
        // Criar pipe para o próximo comando
        if (cmd->next && pipe(cmd->fd) == -1)
        {
            perror("Erro ao criar pipe");
            return;
        }

        // Configuração do heredoc, se existir
        if (cmd->tokens && has_heredoc(mshell, &(cmd->tokens)))
        {
            // O arquivo do heredoc será redirecionado para a entrada do comando atual
            prev_fd = mshell->heredoc_fd; // O heredoc agora se comporta como se fosse o prev_fd
        }

        pid = fork();
        if (pid == 0) // Processo filho
        {
            // Redirecionar entrada do comando anterior ou heredoc, se existir
            if (prev_fd != -1)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                {
                    perror("Erro ao redirecionar stdin do comando anterior ou heredoc");
                    exit(EXIT_FAILURE);
                }
                close(prev_fd);
            }

            // Redirecionar saída para o próximo comando
            if (cmd->next)
            {
                if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
                {
                    perror("Erro ao redirecionar stdout para o próximo comando");
                    exit(EXIT_FAILURE);
                }
                close(cmd->fd[1]);
            }

            // Configurar redirecionamentos (<, >, >>)
            handle_redir(&(cmd->tokens));

            // Fechar descritores desnecessários
            if (cmd->fd[0] != -1)
                close(cmd->fd[0]);

            // Executar o comando
            if (is_builtin(mshell, cmd))
                exit(mshell->e_code);
            else
                run_execve(mshell, cmd->tokens);

            exit(mshell->e_code);
        }

        // Processo pai: fechar descritores desnecessários
        if (prev_fd != -1)
            close(prev_fd);
        if (cmd->next)
            close(cmd->fd[1]);
        prev_fd = cmd->fd[0];

        // Esperar o processo filho terminar
        waitpid(pid, &mshell->e_code, 0);
        if (WIFEXITED(mshell->e_code))
            mshell->e_code = WEXITSTATUS(mshell->e_code);

        // Avançar para o próximo comando
        cmd = cmd->next;
    }
}


bool has_heredoc(t_minishell *mshell, t_token **tokens)
{
    t_token *temp = *tokens;
    int fd;

    while (temp)
    {
        if (temp->type == HEREDOC)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                signal(SIGINT, ft_sigint_hd); // Tratar SIGINT no filho
                read_heredoc(mshell, temp->input, "/tmp/heredoc_file0001");
                exit(0);
            }
            waitpid(pid, &mshell->e_code, 0);
            if (WIFEXITED(mshell->e_code) && WEXITSTATUS(mshell->e_code) != 0)
                return false;

            // Abrir arquivo temporário para redirecionar
            fd = open("/tmp/heredoc_file0001", O_RDONLY);
            if (fd < 0)
            {
                perror("Erro ao abrir arquivo do heredoc");
                return false;
            }
            mshell->heredoc_fd = fd; // Salvar o descritor para o redirecionamento
            remove_token(tokens, &temp);
            return true;
        }
        temp = temp->next;
    }
    return false; // Nenhum heredoc encontrado
}


