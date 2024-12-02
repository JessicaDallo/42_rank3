/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:25:14 by sheila            #+#    #+#             */
/*   Updated: 2024/11/28 15:56:21 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

/*void handle_redirection(t_token *token)
{
    int fd;

    while (token) {
        if (token->type == OUTPUT_REDIR) {
            fd = open(token->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("Error opening file for output redirection");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (token->type == APPEND_REDIR) {
            fd = open(token->value[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("Error opening file for append redirection");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (token->type == INPUT_REDIR) {
            fd = open(token->value[0], O_RDONLY);
            if (fd < 0) {
                perror("Error opening file for input redirection");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        } else if (token->type == HEREDOC) {
            // Lógica para HEREDOC (Simula o conteúdo de entrada com um pipe)
            int pipe_fd[2];
            if (pipe(pipe_fd) < 0) {
                perror("Pipe error for heredoc");
                exit(EXIT_FAILURE);
            }
            write(pipe_fd[1], token->value[0], strlen(token->value[0]));
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
        }
        token = token->next;
    }
}

// Função principal para executar os comandos com pipes e redirections
void execute_commands(t_minishell *shell)
{
    t_token *current = shell->token;
    int pipe_fd[2];
    int prev_fd = -1; // Para conectar pipes
    pid_t pid;

    while (current) {
        if (current->type == CMD) {
            if (current->next && current->next->type == PIPE) {
                if (pipe(pipe_fd) < 0) {
                    perror("Pipe error");
                    exit(EXIT_FAILURE);
                }
            }

            pid = fork();
            if (pid < 0) {
                perror("Fork error");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) { // Processo filho
                if (prev_fd != -1) {
                    dup2(prev_fd, STDIN_FILENO); // Conecta entrada ao pipe anterior
                    close(prev_fd);
                }
                if (current->next && current->next->type == PIPE) {
                    dup2(pipe_fd[1], STDOUT_FILENO); // Conecta saída ao próximo pipe
                    close(pipe_fd[1]);
                }

                // Configura redirections
                handle_redirection(current);

                // Executa o comando
                execve(current->name, current->value, shell->envp);
                perror("Execve error");
                exit(EXIT_FAILURE);
            }

            // Processo pai
            if (prev_fd != -1) {
                close(prev_fd); // Fecha a extremidade do pipe anterior
            }
            if (current->next && current->next->type == PIPE) {
                close(pipe_fd[1]); // Fecha a extremidade de escrita do pipe
                prev_fd = pipe_fd[0]; // Salva a extremidade de leitura para o próximo comando
            }

            // Avança para o próximo token após o pipe
            current = current->next && current->next->type == PIPE ? current->next->next : current->next;

        } else {
            current = current->next;
        }
    }

    // Espera todos os processos filhos
    while (wait(NULL) > 0);
}

t_token *create_token(token_type type, char *name, char **value)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->name = strdup(name);
	token->value = value; // Apenas atribuímos; não alocamos
	token->next = NULL;
	return token;
}

// Função para adicionar um token ao final da lista
void append_token(t_token **head, t_token *new_token)
{
	t_token *current = *head;
	if (!current)
	{
		*head = new_token;
		return;
	}
	while (current->next)
		current = current->next;
	current->next = new_token;
}

// Função para liberar os tokens
void free_tokens(t_token *head)
{
	t_token *current = head;
	while (current)
	{
		t_token *tmp = current;
		current = current->next;
		free(tmp->name);
		// NÃO liberar tmp->value, pois não foi alocado dinamicamente
		free(tmp);
	}
}

// Main para testar
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// Inicialização do minishell
	t_minishell shell;
	shell.env = NULL;
	shell.token = NULL;
	shell.envp = envp;
	shell.e_code = 0;
	shell.env_size = 0;

	// Comandos de teste
	// Simula: cat Makefile | grep NAME > output.txt
	char *cat_args[] = {"cat", "Makefile", NULL};
	char *grep_args[] = {"grep", "NAME", NULL};

	// Criando tokens
	append_token(&shell.token, create_token(CMD, "/bin/cat", cat_args));
	append_token(&shell.token, create_token(PIPE, "|", NULL));
	append_token(&shell.token, create_token(CMD, "/bin/grep", grep_args));
	append_token(&shell.token, create_token(OUTPUT_REDIR, ">", (char *[]){"output.txt", NULL}));

	// Executa os comandos
	execute_commands(&shell);

	// Libera a memória dos tokens
	free_tokens(shell.token);

	return 0;
}*/