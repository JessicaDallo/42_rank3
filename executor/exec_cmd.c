/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:25:14 by sheila            #+#    #+#             */
/*   Updated: 2024/12/11 16:59:47 by shrodrig         ###   ########.fr       */
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
        has_heredoc(mshell, cmd);
        //handle_redir(cmd->tokens);
	    if(is_builtin(mshell, cmd))
		    return;
	    else
		    run_execve(mshell, cmd->tokens);
        cmd = cmd->next;
    }
	return;
}

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
	mshell.commands->tokens = cr_sample_tokens();
	exec_cmd(&mshell);
	printf("\nEXIT CODE Main: %d\n", mshell.e_code);
	clear_mshell(&mshell);
    return 0;
}