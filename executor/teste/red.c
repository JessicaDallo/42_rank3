#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <linux/limits.h>
#include <fcntl.h>

/*int main() {
    // Abrir o arquivo para redirecionamento de saída
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Redireciona a saída padrão para o arquivo
    dup2(fd, STDOUT_FILENO);

    // Fecha o descritor de arquivo, pois não será mais necessário
    close(fd);

    // Executa o comando (por exemplo, `ls`)
    char *args[] = { "ls", NULL };
    execvp("ls", args);

    // Se o exec falhar, exibe uma mensagem de erro
    perror("Erro ao executar o comando");
    return 1;
}

void	redir_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if(fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Erro ao redirecionar o arquivo");
		return;
	}
	close(fd);	
}

void	redir_output(char *file, char *redir)
{
	int	fd;
	
	if(!redir[1])
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Erro ao redirecionar o arquivo");
		return;
	}
	close(fd);	
}

void	redir_error(char *file, char *redir)
{
	int	fd;
	
	if(!redir[2])
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return;
	}
	if (dup2(fd, STDERR_FILENO) < 0)
	{
		perror("Erro ao redirecionar o arquivo");
		return;
	}
	close(fd);	
}


void	handle_redir(char *file, char *redir)
{
	if(!strchr(redir, "<"))
		redir_input(file);
	else if(!strcmp(redir, ">"))
		redir_output(file, redir);	
	else if(!strcmp(redir, ">>"))
		redir_output(file, redir);
	else if(!strcmp(redir, "2>"))
		redir_error(file, redir);
	else if(!strcmp(redir, "2>>"))
		redir_error(file, redir);
}

int main()
{
	handle_redir("output.txt", ">>");
	char *args[] = { "ls", NULL };
	execvp("ls", args);
	perror("Erro ao executar o comando");
	return 1;
}*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_redir {
    char *input_file;
    char *output_file;
    char *error_file;
    int append_output;
    int append_error;
} t_redir;

void parse_command(char *cmd, char **command, t_redir *redir) {
    char *token = strtok(cmd, " ");
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            redir->output_file = strdup(token);
            redir->append_output = 0;
        } else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " ");
            redir->output_file = strdup(token);
            redir->append_output = 1;
        } else if (strcmp(token, "2>") == 0) {
            token = strtok(NULL, " ");
            redir->error_file = strdup(token);
            redir->append_error = 0;
        } else if (strcmp(token, "2>>") == 0) {
            token = strtok(NULL, " ");
            redir->error_file = strdup(token);
            redir->append_error = 1;
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " ");
            redir->input_file = strdup(token);
        } else {
            *command = strdup(token);
        }
        token = strtok(NULL, " ");
    }
}

void handle_redirections(t_redir *redir) {
    int fd;

    if (redir->input_file) {
        fd = open(redir->input_file, O_RDONLY);
        if (fd < 0) {
            perror("Erro ao abrir arquivo de entrada");
            exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (redir->output_file) {
        if (redir->append_output) {
            fd = open(redir->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        } else {
            fd = open(redir->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        if (fd < 0) {
            perror("Erro ao abrir arquivo de saída");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    if (redir->error_file) {
        if (redir->append_error) {
            fd = open(redir->error_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        } else {
            fd = open(redir->error_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        if (fd < 0) {
            perror("Erro ao abrir arquivo de erro");
            exit(1);
        }
        dup2(fd, STDERR_FILENO);
        close(fd);
    }
}

int main() {
    char *command = NULL;
    t_redir redir = {0};

    // Exemplo de comando com redirecionamento
    //char cmd[] = "ls > output.txt 2> error.txt < input.txt";
    char cmd[] = "cat > output.txt < input.txt";

    // Parsear o comando para identificar os redirecionamentos
    parse_command(cmd, &command, &redir);

    // Configurar os redirecionamentos
    handle_redirections(&redir);

    // Executar o comando com execve
    char *args[] = {command, NULL};
    //char *args[] = {"/bin/ls", "/diretorio_inexistente", NULL}; 
    
    execve("/bin/cat", args, NULL); 
    
    // Libera a memória alocada para o comando e redirecionamentos
    free(command);
    free(redir.input_file);
    free(redir.output_file);
    free(redir.error_file);

    return 0;
}


