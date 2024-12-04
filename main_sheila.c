/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sheila.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:31:29 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/04 17:59:24 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

// void creat_tokens(char *arg, t_minishell *mshell)
// {
//     t_cmd *temp;
//     char **tokens;
//     char **comd;
//     int i;

// 	mshell->commands = NULL;
//     // Inicialize tokens com o resultado de ft_split
//     tokens = ft_split(arg, '|');
//     if (!tokens)
//         return; // Verifique se o split falhou

//     i = 0;
//     while (tokens[i])
//     {
//         // Inicializar o comando atual
//         temp = malloc(sizeof(t_cmd));
//         if (!temp)
//         {
//             perror("malloc");
//             exit(EXIT_FAILURE); // Interrompa o programa em caso de erro
//         }
//         ft_bzero(temp, sizeof(t_cmd));

//         // Divida o comando atual nos argumentos
//         comd = ft_split(tokens[i], ' ');
//         if (!comd || !comd[0])
//         {
//             free(temp);
//             i++;
//             continue; // Ignorar tokens vazios
//         }

//         // Inicializar o comando e entradas
//         temp->cmd = ft_strdup(comd[0]); // Copiar o comando principal
//         if (!temp->cmd)
//         {
//             perror("ft_strdup");
//             exit(EXIT_FAILURE);
//         }

//         int j = 0; // Começar do segundo argumento
//         int input_count = 0;

//         // Alocar para `input` (assumindo no máximo 10 argumentos; ajuste conforme necessário)
//         temp->input = malloc(sizeof(char *) * 11);
//         if (!temp->input)
//         {
//             perror("malloc");
//             exit(EXIT_FAILURE);
//         }

//         // Copiar argumentos para o array de entrada
//         while (comd[j])
//         {
//             temp->input[input_count++] = ft_strdup(comd[j]);
//             if (!temp->input[input_count - 1])
//             {
//                 perror("ft_strdup");
//                 exit(EXIT_FAILURE);
//             }
//             j++;
//         }
//         temp->input[input_count] = NULL; // Finalizar array com NULL

//         // Adicionar `temp` à lista de comandos no `mshell`
//         if (!mshell->commands)
//             mshell->commands = temp;
//         else
//         {
//             t_cmd *last = mshell->commands;
//             while (last->next)
//                 last = last->next;
//             last->next = temp;
//         }

//         // Liberar `comd` e seguir para o próximo token
//         j = 0;
//         while (comd[j])
//             free(comd[j++]);
//         free(comd);
//         i++;
//     }

// 	//executable(mshell, mshell->commands);
//     //Liberar tokens
//     i = 0;
//     while (tokens[i])
//         free(tokens[i++]);
//     free(tokens);
// }


/*int main(int argc, char **argv, char **envp)
{
    t_minishell *mshell;
	
	(void)argv;
	(void)argc;
    
   	mshell = malloc(sizeof(t_minishell));
    init_struct(mshell, envp);
	char	*input = NULL;
	while (1)
	{
		signal(SIGINT, ft_sigint);
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if(*input)
			add_history(input);
		//if (validate(&input) > 0)
			//continue;
		//creat_tokens(input, mshell);
		//if(input[0] == '<' && input[1] == '<')
		//{
		//	char *end = (input + 2);
		//	here_doc(mshell, end);
		//}
		//executable(mshell, mshell->commands);
		//get_tokens(input);
		//t_token **tokens = tokenize(const char *input)
	}
}*/