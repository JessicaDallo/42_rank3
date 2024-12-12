/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Crd: 2024/11/03 22:11:06 by sheila            #+#    #+#             */
/*   Updated: 2024/12/04 17:42:31 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

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

void	redir_output(char *file)
{
	int	fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	redir_append(char *file)
{
	int	fd;
	
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

// void	redir_error(char *file)
// {
// 	int	fd;
	
// 	if(!redir[2])
// 		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else
// 		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if(fd < 0)
// 	{
// 		perror("Erro ao abrir o arquivo");
// 		return;
// 	}
// 	if (dup2(fd, STDERR_FILENO) < 0)
// 	{
// 		perror("Erro ao redirecionar o arquivo");
// 		return;
// 	}
// 	close(fd);	
// }

void    remove_redir(t_token *tokens)
{
    t_token   *temp;
    t_token   *aux;

    temp = tokens;
    aux = NULL;
	printf("FIRST REMOVE:\n");
    while(temp)
    {
        if(tokens->type == INPUT_REDIR || tokens->type == OUTPUT_REDIR ||
			tokens->type == APPEND_REDIR)
        {
            if (aux)
                aux->next = temp->next;
            else
                tokens = temp->next;
            free(temp->input);
            free(temp);
            return;
        }
        aux = temp;
        temp = temp->next; 
    }
	return;
}

void	handle_redir(t_token *tokens)
{
	//Lidar com expnsao do tilde
	while(tokens)
	{
		if(tokens->type == INPUT_REDIR)
		{
			redir_input(tokens->input);
			remove_redir(tokens);
		}
		else if(tokens->type == OUTPUT_REDIR)
		{
			redir_output(tokens->input);
			remove_redir(tokens);	
		}
		else if(tokens->type == APPEND_REDIR)
		{
			redir_append(tokens->input);
			remove_redir(tokens);
		}
		tokens = tokens->next;
	}
}

// t_token *cr_token(token_type type, const char *input)
// {
//     t_token *new_token = malloc(sizeof(t_token));
//     if (!new_token)
//         return NULL;
//     new_token->type = type;
//     new_token->input = strdup(input); // Copia o valor da string
//     new_token->next = NULL;
//     return new_token;
// }

// t_token *cr_sample_tokens()
// {
//     t_token *token1 = cr_token(CMD, "echo");
// 	t_token *token2 = cr_token(ARG, "ola");
//     t_token *token3 = cr_token(OUTPUT_REDIR, "test.txt");
//     t_token *token4 = cr_token(ARG, "bom");
//     t_token *token5 = cr_token(ARG, "dia");
// 	t_token *token6 = cr_token(OUTPUT_REDIR, "new.txt");

//     // Conecte os tokens
//     token1->next = token2;
//     token2->next = token3;
// 	token3->next = token4;
//     token4->next = token5;
// 	token5->next = token6;

//     return token1; // Retorna o início da lista
// }

// int main()
// {
//     t_token *tokens = cr_sample_tokens();

//     printf("Antes de handle_redir:\n");
//     t_token *temp = tokens;
//     while (temp)
//     {
//         printf("Token type: %d, input: %s\n", temp->type, temp->input);
//         temp = temp->next;
//     }

//     handle_redir(tokens);

//     printf("\nDepois de handle_redir (se remover os tokens):\n");
//     temp = tokens;
//     while (temp)
//     {
//         printf("Token type: %d, input: %s\n", temp->type, temp->input);
//         temp = temp->next;
//     }
//     return 0;
// }

