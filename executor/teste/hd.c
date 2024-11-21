#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

void execute_heredoc(const char *delim, const char *cmd[], const char *output_file, const char *var_name, const char *var_value) {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processo filho para executar o comando
        close(pipe_fd[1]); // Fecha o lado de escrita

        if (output_file) {
            int file_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (file_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(file_fd, STDOUT_FILENO); // Redireciona a saída para o arquivo
            close(file_fd);
        } else {
            dup2(pipe_fd[0], STDIN_FILENO); // Redireciona stdin para o pipe
        }

        execvp(cmd[0], (char *const *)cmd); // Executa o comando
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // Processo pai para capturar o heredoc
    close(pipe_fd[0]); // Fecha o lado de leitura no pai

    char *line = NULL;
    size_t len = 0;
    while (1) {
        printf("heredoc> ");
        if (getline(&line, &len, stdin) == -1 || strcmp(line, delim) == 0) {
            break; // Sai do loop ao encontrar o delimitador
        }

        // Expansão de variável simples
        if (var_name && var_value && strstr(line, var_name)) {
            char *expanded_line = malloc(strlen(line) + strlen(var_value));
            sprintf(expanded_line, line, var_value);
            write(pipe_fd[1], expanded_line, strlen(expanded_line));
            free(expanded_line);
        } else {
            write(pipe_fd[1], line, strlen(line));
        }
    }

    free(line);
    close(pipe_fd[1]); // Fecha o lado de escrita do pipe
    waitpid(pid, NULL, 0); // Espera o processo filho terminar
}

int main() {
    // Exemplos de uso

    // 1. cat << EOF
    const char *cmd1[] = {"cat", NULL};
    execute_heredoc("EOF\n", cmd1, NULL, NULL, NULL);

    // 2. grep "pattern" << END
    const char *cmd2[] = {"grep", "pattern", NULL};
    execute_heredoc("END\n", cmd2, NULL, NULL, NULL);

    // 3. cat << EOF | grep "pattern"
    const char *cmd3[] = {"grep", "pattern", NULL};
    execute_heredoc("EOF\n", cmd1, NULL, NULL, NULL);
    execute_heredoc("EOF\n", cmd3, NULL, NULL, NULL);

    // 4. cat << FIM > arquivo.txt
    const char *cmd4[] = {"cat", NULL};
    execute_heredoc("FIM\n", cmd4, "arquivo.txt", NULL, NULL);

    // 5. while read line << EOF
    const char *cmd5[] = {"cat", NULL}; // Alterar para o comando desejado
    execute_heredoc("EOF\n", cmd5, NULL, NULL, NULL);

    // 6. Variável no heredoc
    const char *cmd6[] = {"cat", NULL};
    execute_heredoc("EOF\n", cmd6, NULL, "$NOME", "usuário");

    return 0;
}