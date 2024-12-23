/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_exec_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:35:42 by sheila            #+#    #+#             */
/*   Updated: 2024/12/23 18:03:55 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//void exec_cmd(t_minishell *mshell)
//{
//    t_cmd   *cmd;
//    pid_t   pid;
//    int     prev_fd;

//    cmd = mshell->commands;
//    prev_fd = -1;
//    create_pipes(cmd);
//    while (cmd)
//    {
//        //se houver cmd->next?
//        if (cmd->tokens && has_heredoc(mshell, &(cmd->tokens)))
//            prev_fd = mshell->heredoc_fd;

//        pid = creat_pid(mshell);
//        if (pid == 0)
//        {
//            if (prev_fd != -1)
//                redir_fds(prev_fd, STDIN_FILENO);
//            // Redirecionar saída para o próximo comando
//            if (cmd->next)
//                redir_fds(cmd->fd[1], STDOUT_FILENO);
//            // Configurar redirecionamentos (<, >, >>)
//            handle_redir(&(cmd->tokens));
//            // Fechar descritores desnecessários
//            if (cmd->fd[0] != -1)
//                close(cmd->fd[0]);
//            // Executar o comando
//            if (is_builtin(mshell, cmd))
//                exit(mshell->e_code);
//            else
//                run_execve(mshell, cmd->tokens);
//            exit(mshell->e_code);
//        }
//        // Processo pai: fechar descritores desnecessários
//        if (prev_fd != -1)
//            close(prev_fd);
//        if (cmd->next)
//            close(cmd->fd[1]);
//        prev_fd = cmd->fd[0];
//        // Esperar o processo filho terminar
//        waitpid(pid, &mshell->e_code, 0);
//        if (WIFEXITED(mshell->e_code))
//            mshell->e_code = WEXITSTATUS(mshell->e_code);
//        // Avançar para o próximo comando
//        cmd = cmd->next;
//    }
//}


/*void	exec_cmd(t_minishell *mshell)
{
    t_cmd   *cmd;
    
    cmd = mshell->commands;
    while(cmd)
    {
        if(!cmd->tokens || !cmd->tokens->input)
        {
            clear_mshell(mshell);
            return;
        }
        has_heredoc(mshell, &(cmd->tokens)); //Lidar com rediecionamento de input do heredoc
        handle_redir(&(cmd->tokens));
        if(cmd->tokens)
        {
	        if(is_builtin(mshell, cmd))
		        return;
	        else
		        run_execve(mshell, cmd->tokens);
        }
        cmd = cmd->next;
    }
}*/

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
        //printf("[DEBUG] Pipe criado: fd[0] = %d, fd[1] = %d\n", cmd->fd[0], cmd->fd[1]);
        pid = creat_pid(mshell);
        if (pid == 0) // Processo filho
        {
            // Configurar entrada (heredoc ou input file)
            has_heredoc(mshell, &(cmd->tokens));// Configura o stdin para o heredoc
            handle_redir(&(cmd->tokens)); // Configura redirecionamentos (<, >, >>)

            // Configurar saída (pipe para o próximo comando, se existir)
            if (prev_fd != -1)
            {
                if(dup2(prev_fd, STDIN_FILENO) == -1)
                    perror("[DEBUG] Erro em dup2 (prev_fd -> STDIN)");
                close(prev_fd);
            }

            // Redirecionar saída, se necessário
            if (cmd->next)
            {
                if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
                    perror("[DEBUG] Erro em dup2 (fd[1] -> STDOUT)");
                else
                    //printf("[DEBUG] Redirecionado STDOUT para fd[1]: %d\n", cmd->fd[1]);
                close(cmd->fd[1]);
            }

            // Fechar descritores desnecessários
            if (cmd->fd[0] != -1)
                close(cmd->fd[0]);

            // Executar comando
            //printf("[DEBUG] Executando comando: %s\n", cmd->tokens->input);
            if (is_builtin(mshell, cmd))
                exit(mshell->e_code);
                //return;
            else
                run_execve(mshell, cmd->tokens);  
            exit(mshell->e_code);
        }
         if (prev_fd != -1)
            close(prev_fd);
        //if (cmd->fd[0] != -1)
            //close(cmd->fd[0]);
        if (cmd->next)
            close(cmd->fd[1]);
        prev_fd = cmd->fd[0];
        waitpid(pid, &mshell->e_code, 0);
	    if(WIFEXITED(mshell->e_code))
		    mshell->e_code = WEXITSTATUS(mshell->e_code);
        // Fechar descritores não mais usados
        // Atualizar para o próximo comando
        cmd = cmd->next;
    }
    //while (waitpid(-1, &mshell->e_code, 0) > 0)
    //    ;
    //if (WIFEXITED(mshell->e_code))
    //    mshell->e_code = WEXITSTATUS(mshell->e_code);
}

void	has_heredoc(t_minishell *mshell, t_token **tokens)
{
	t_token *temp;
    t_token *aux;
    int fd = -1;
	
	temp = *tokens;
	while(temp)
	{
        //printf("Iterando no token: %s\n", temp->input);
        aux = temp->next;
        if (temp->type == HEREDOC)
        {   
            //printf("\n ****** HAS_HEREDOC FILHO ******\n");
            pid_t pid = creat_pid(mshell);
            //printf("PID criado: %d\n", pid);
            signal(SIGINT, SIG_IGN); // Ignorar SIGINT no processo principal
	        signal(SIGQUIT, SIG_IGN); 
            if(pid == 0)
            {
                //printf("Processo filho iniciado para HEREDOC.\n");
                signal(SIGINT, ft_sigint_hd); //signal_HEREDOC - E PRECISO NOS DOIS?
                ft_heredoc(mshell, temp->input);
                //printf("Processo filho finalizando.\n");
                exit(mshell->e_code);
            }
            //printf("Aguardando filho com waitpid.\n");
            waitpid(pid, &mshell->e_code, 0);
            //printf("Filho finalizado, status: %d\n", mshell->e_code);
	        if(WIFEXITED(mshell->e_code))
		    mshell->e_code = WEXITSTATUS(mshell->e_code);
            //printf("Removendo token HEREDOC.\n");
            if (fd > 0)
				close(fd);

			// Abre o novo arquivo temporário (último HEREDOC)
			fd = open("/tmp/heredoc_file0001", O_RDONLY);
			if (fd < 0)
			{
				perror("Erro ao abrir arquivo temporário");
				return;
			}
            remove_token(tokens, &temp);
        }
        temp = aux;
    }
    if (fd >= 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			perror("Erro ao redirecionar stdin");
		close(fd);
	}
    //printf("Finalizando has_heredoc.\n");
    return;
}*/



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

t_cmd *cr_cmd(void)
{
    t_cmd *new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return NULL;

    new_cmd->tokens = NULL;  // Inicializa a lista de tokens como vazia
    new_cmd->fd[0] = -1;     // Inicializa os descritores de arquivo
    new_cmd->fd[1] = -1;
    new_cmd->next = NULL;    // Inicializa o próximo comando como NULL

    return new_cmd;
}
void add_token_to_cmd(t_cmd *cmd, t_token *token)
{
    t_token *current;

    if (!cmd || !token)
        return;

    if (!cmd->tokens)
    {
        cmd->tokens = token; // Se a lista de tokens estiver vazia, define o primeiro token
    }
    else
    {
        current = cmd->tokens;
        while (current->next)
            current = current->next; // Percorre até o final da lista de tokens
        current->next = token;       // Adiciona o token ao final
    }
}

t_cmd *cr_sample_cmds()
{
    // Comando 1: cat com HEREDOC
    t_cmd *cmd1 = cr_cmd();
    //add_token_to_cmd(cmd1// Verifica se o processo filho terminou normalmente (sem sinais, cr_token(CMD, "echo"));
    //add_token_to_cmd(cmd1, cr_token(ARG, "ola,"));
    //add_token_to_cmd(cmd1, cr_token(ARG, "$USER"));
    //add_token_to_cmd(cmd1, cr_token(CMD, "grep"));
    //add_token_to_cmd(cmd1, cr_token(INPUT_REDIR, "Makefile"));
    //add_token_to_cmd(cmd1, cr_token(INPUT_REDIR, "abc.txt"));
    //add_token_to_cmd(cmd1, cr_token(ARG, "NAME"));
    //add_token_to_cmd(cmd1, cr_token(APPEND_REDIR, "def.txt"));
    //add_token_to_cmd(cmd1, cr_token(ARG, "TESTEEEEEEEEEEEE"));
    add_token_to_cmd(cmd1, cr_token(CMD, "cat"));
    add_token_to_cmd(cmd1, cr_token(HEREDOC, "END"));
    add_token_to_cmd(cmd1, cr_token(HEREDOC, "stop"));
    add_token_to_cmd(cmd1, cr_token(OUTPUT_REDIR, "abc.txt"));
    add_token_to_cmd(cmd1, cr_token(ARG, "Makefile"));
    //add_token_to_cmd(cmd1, cr_token(OUTPUT_REDIR, "def.txt"));
   // add_token_to_cmd(cmd1, cr_token(ARG, "new.txt"));
    
    // Comando 2: echo com argumentos
    // t_cmd *cmd2 = cr_cmd();
    // add_token_to_cmd(cmd2, cr_token(CMD, "echo"));
    // add_token_to_cmd(cmd2, cr_token(ARG, "Hello World"));

    // Conecte os comandos
    //cmd1->next = cmd2;

    return cmd1; // Retorna o início da lista de comandos
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    init_struct(&mshell, envp);
	//mshell.commands = malloc(sizeof(t_cmd));
    //if (!mshell.commands)
      //  return (1);
    //ft_bzero(mshell.commands, sizeof(t_cmd));
	mshell.commands = cr_sample_cmds();
	exec_cmd(&mshell);
	printf("\nEXIT CODE Main: %d\n", mshell.e_code);
	clear_mshell(&mshell);
    return 0;
}*/




// void handle_pipes(t_minishell *mshell, t_cmd *cmd)
// {
//     int fds[2];
//     //int fd_in = 0;
//     pid_t pid;
    
//     pipe(fds);
//     pid = creat_pid(mshell); // Cria o pipe para conectar os comandos
//     if (pid == 0)
//     {
//         //dup2(fd_in, STDIN_FILENO); // primeiro comando
//         dup2(fds[1], STDOUT_FILENO); 
//         close(fds[0]);
//         //handle_redir(cmd->name, cmd->value);
//         exec_cmd(mshell, cmd);
//     }s
//     else
//     {
//         waitpid(pid, &mshell->e_code, 0);
//         close(fds[1]); 
//         //fd_in = fds[0];
//     }
//     cmd = cmd->next;
// }

// void    rm_token(t_token *tokens)
// {
//     t_token   *temp;
//     t_token   *aux;

//     temp = tokens;
//     while(temp)
//     {
//         aux = temp;
//         temp = temp->next;
//         free(aux);
//     }
//     return;   
// }

// void    rm_cmd(t_cmd **command, int size)
// {
//     t_cmd   *temp;
//     t_cmd   *aux;
//     int     i;

//     temp = *command;
//     i = 0;
//     while(temp && i < size)
//     {
//         aux = temp->next;
//         rm_tokens(temp->tokens);
//         free(temp);
//         temp = aux;
//         i++; 
//     }
//     *
// 	return;
// }





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

//void exec_cmd(t_minishell *mshell)
//{
//    t_cmd *cmd = mshell->commands;
//    pid_t pid;
//    int prev_fd = -1;

//    while (cmd)
//    {
//        // Criar pipe para o próximo comando
//        if (cmd->next && pipe(cmd->fd) == -1)
//        {
//            perror("Erro ao criar pipe");
//            return;
//        }

//        // Configuração do heredoc, se existir
//        if (cmd->tokens && has_heredoc(mshell, &(cmd->tokens)))
//        {
//            // O arquivo do heredoc será redirecionado para a entrada do comando atual
//            prev_fd = mshell->heredoc_fd; // O heredoc agora se comporta como se fosse o prev_fd
//        }

//        pid = fork();
//        if (pid == 0) // Processo filho
//        {
//            // Redirecionar entrada do comando anterior ou heredoc, se existir
//            if (prev_fd != -1)
//            {
//                if (dup2(prev_fd, STDIN_FILENO) == -1)
//                {
//                    perror("Erro ao redirecionar stdin do comando anterior ou heredoc");
//                    exit(EXIT_FAILURE);
//                }
//                close(prev_fd);
//            }

//            // Redirecionar saída para o próximo comando
//            if (cmd->next)
//            {
//                if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
//                {
//                    perror("Erro ao redirecionar stdout para o próximo comando");
//                    exit(EXIT_FAILURE);
//                }
//                close(cmd->fd[1]);
//            }

//            // Configurar redirecionamentos (<, >, >>)
//            handle_redir(&(cmd->tokens));

//            // Fechar descritores desnecessários
//            if (cmd->fd[0] != -1)
//                close(cmd->fd[0]);

//            // Executar o comando
//            if (is_builtin(mshell, cmd))
//                exit(mshell->e_code);
//            else
//                run_execve(mshell, cmd->tokens);

//            exit(mshell->e_code);
//        }

//        // Processo pai: fechar descritores desnecessários
//        if (prev_fd != -1)
//            close(prev_fd);
//        if (cmd->next)
//            close(cmd->fd[1]);
//        prev_fd = cmd->fd[0];

//        // Esperar o processo filho terminar
//        waitpid(pid, &mshell->e_code, 0);
//        if (WIFEXITED(mshell->e_code))
//            mshell->e_code = WEXITSTATUS(mshell->e_code);

//        // Avançar para o próximo comando
//        cmd = cmd->next;
//    }
//}


//bool has_heredoc(t_minishell *mshell, t_token **tokens)
//{
//    t_token *temp = *tokens;
//    int fd;

//    while (temp)
//    {
//        if (temp->type == HEREDOC)
//        {
//            pid_t pid = fork();
//            if (pid == 0)
//            {
//                signal(SIGINT, ft_sigint_hd); // Tratar SIGINT no filho
//                read_heredoc(mshell, temp->input, "/tmp/heredoc_file0001");
//                exit(0);
//            }
//            waitpid(pid, &mshell->e_code, 0);
//            if (WIFEXITED(mshell->e_code) && WEXITSTATUS(mshell->e_code) != 0)
//                return false;

//            // Abrir arquivo temporário para redirecionar
//            fd = open("/tmp/heredoc_file0001", O_RDONLY);
//            if (fd < 0)
//            {
//                perror("Erro ao abrir arquivo do heredoc");
//                return false;
//            }
//            mshell->heredoc_fd = fd; // Salvar o descritor para o redirecionamento
//            remove_token(tokens, &temp);
//            return true;
//        }
//        temp = temp->next;
//    }
//    return false; // Nenhum heredoc encontrado
//}


