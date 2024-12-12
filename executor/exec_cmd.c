/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:25:14 by sheila            #+#    #+#             */
/*   Updated: 2024/12/12 19:51:08 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	exec_cmd(t_minishell *mshell)
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
        has_heredoc(mshell, cmd); //Lidar com rediecionamento de input do heredoc
        handle_redir(cmd->tokens);
	    if(is_builtin(mshell, cmd))
		    return;
	    else
		    run_execve(mshell, cmd->tokens);
        cmd = cmd->next;
    }
	return;
}

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
        pipe(cmd->fd);
        dup2(cmd->fd[1], STDOUT_FILENO); 
        close(cmd->fd[0]);
        has_heredoc(mshell, cmd);
        //handle_redir(cmd->tokens);
	    if(is_builtin(mshell, cmd))
		    return;
	    else
		   run_execve(mshell, cmd->tokens);
        close(cmd->fd[1]);
	    if(WIFEXITED(mshell->e_code)) // Verifica se o processo filho terminou normalmente (sem sinais)
		mshell->e_code = WEXITSTATUS(mshell->e_code);
        cmd = cmd->next;
    }
	return;
}*/

void	has_heredoc(t_minishell *mshell, t_cmd *cmd)
{
	t_token *temp;
    t_token *prev;
	
	temp = cmd->tokens;
	while(temp)
	{
        if (temp->type == HEREDOC)
        {
            ft_heredoc(mshell, temp->input);
            if(prev)
                prev->next = temp->next;
            else
                cmd->tokens = temp->next;
            free(temp->input);
            free(temp);
        }
        prev = temp;
		temp = temp->next;
	}
	return;
}

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

// void	run_commands(t_minishell *mshell)
// {
// 	t_cmd	*cmd;

// 	cmd = mshell->commands;
// 	while(cmd)
// 	{
// 		if (!cmd->next)
// 			exec_cmd(mshell, cmd);
// 		else if (cmd->next)
//             handle_pipes(mshell, cmd);
// 		//else if (commands->type == OUTPUT_REDIR)
// 		//	//função
// 		//else if (commands->type == APPEND_REDIR)
// 		//	//função
// 		//else if (commands->type == INPUT_REDIR)
// 		//	//função
// 		//else if (commands->type == HEREDOC)
// 		//	//função
// 		cmd = cmd->next;
// 	}
// }


t_token *cr_token(token_type type, const char *input)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->input = strdup(input); // Copia o valor da string
    new_token->next = NULL;
    return new_token;
}

/*t_token *cr_sample_tokens()
{
    t_token *token1 = cr_token(CMD, "cat");
    t_token *token2 = cr_token(HEREDOC, "STOP");
    //t_token *token3 = cr_token(CMD, "echo");
	//t_token *token4 = cr_token(ARG, "Makefile");
    //t_token *token5 = cr_token(ARG, "new.txt");
    //t_token *token6 = cr_token(OUTPUT_REDIR, "teste.txt");

    // Conecte os tokens
    token1->next = token2;
    //token2->next = token3;
	//token3->next = token4;
    //token4->next = token5;
	//token5->next = token6;;

    return token1; // Retorna o início da lista
}*/

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
    add_token_to_cmd(cmd1, cr_token(CMD, "cat"));
    //add_token_to_cmd(cmd1, cr_token(HEREDOC, "END"));
    add_token_to_cmd(cmd1, cr_token(ARG, "Makefile"));
    add_token_to_cmd(cmd1, cr_token(OUTPUT_REDIR, "test.txt"));
    add_token_to_cmd(cmd1, cr_token(OUTPUT_REDIR, "test2.txt"));
    //add_token_to_cmd(cmd1, cr_token(HEREDOC, "stop"));
    
    // Comando 2: echo com argumentos
    //t_cmd *cmd2 = cr_cmd();
    //add_token_to_cmd(cmd2, cr_token(CMD, "echo"));
    //add_token_to_cmd(cmd2, cr_token(ARG, "Hello World"));

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
	mshell.commands = malloc(sizeof(t_cmd));
    if (!mshell.commands)
        return (1);
    ft_bzero(mshell.commands, sizeof(t_cmd));
	mshell.commands = cr_sample_cmds();
	exec_cmd(&mshell);
	printf("\nEXIT CODE Main: %d\n", mshell.e_code);
	clear_mshell(&mshell);
    return 0;
}