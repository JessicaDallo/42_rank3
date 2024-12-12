/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:15:14 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/12 17:34:01 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void exec_cmd(t_minishell *mshell)
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
            has_heredoc(mshell, cmd); // Configura o stdin para o heredoc
            handle_redir(cmd->tokens); // Configura redirecionamentos (<, >, >>)

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
                exit(mshell->e_code);
            else
                run_execve(mshell, cmd->tokens);
        }

        // Processo pai
        waitpid(pid, &mshell->e_code, 0);

        // Fechar descritores não mais usados
        if (cmd->fd[1] != -1)
            close(cmd->fd[1]);

        // Atualizar para o próximo comando
        cmd = cmd->next;
    }
}

void has_heredoc(t_minishell *mshell, t_cmd *cmd)
{
    t_token *temp = cmd->tokens;
    t_token *prev = NULL;

    while (temp)
    {
        if (temp->type == HEREDOC)
        {
            int fd_here = tmp_heredoc(mshell);
            if (fd_here < 0)
                return;

            read_heredoc(mshell, temp->input, true);
            if (dup2(fd_here, STDIN_FILENO) < 0)
            {
                perror("Error redirecting heredoc to stdin");
                close(fd_here);
                return;
            }
            //close(fd_here);

            // Remover o token HEREDOC após processar
            if (prev)
                prev->next = temp->next;
            else
                cmd->tokens = temp->next;

            free(temp->input);
            free(temp);
            return; // Apenas um heredoc é esperado por comando
        }
        prev = temp;
        temp = temp->next;
    }
}

void handle_redir(t_token *tokens)
{
    t_token *temp = tokens;

    while (temp)
    {
        if (temp->type == INPUT_REDIR) // <
        {
            int fd = open(temp->input, O_RDONLY);
            if (fd < 0)
            {
                perror("Error opening input file");
                return;
            }
            if (dup2(fd, STDIN_FILENO) < 0)
                perror("Error redirecting input file to stdin");
            close(fd);
        }
        else if (temp->type == OUTPUT_REDIR) // >
        {
            int fd = open(temp->input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("Error opening output file");
                return;
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
                perror("Error redirecting output file to stdout");
            close(fd);
        }
        else if (temp->type == APPEND_REDIR) // >>
        {
            int fd = open(temp->input, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror("Error opening append file");
                return;
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
                perror("Error redirecting append file to stdout");
            close(fd);
        }
        temp = temp->next;
    }
}


/*t_token *cr_token(token_type type, const char *input)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->input = strdup(input); // Copia o valor da string
    new_token->next = NULL;
    return new_token;
}

t_token *cr_sample_tokens()
{
    t_token *token1 = cr_token(CMD, "cat");
    t_token *token2 = cr_token(HEREDOC, "END");
	//t_token *token3 = cr_token(ARG, "Makefile");
    //t_token *token4 = cr_token(ARG, "new.txt");
    //t_token *token5 = cr_token(OUTPUT_REDIR, "teste.txt");
	//t_token *token6 = cr_token(ARG, "");

    // Conecte os tokens
    token1->next = token2;
    //token2->next = token3;
	//token3->next = token4;
    //token4->next = token5;
	//token5->next = token6;;

    return token1; // Retorna o início da lista
}*/

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    init_struct(&mshell, envp);
	mshell.commands = malloc(sizeof(t_cmd));
    if (!mshell.commands)
        return (1);
    ft_bzero(mshell.commands, sizeof(t_cmd));
	mshell.commands = cr_cmd();
	exec_cmd(&mshell);
	printf("\nEXIT CODE Main: %d\n", mshell.e_code);
	clear_mshell(&mshell);
    return 0;
}*/