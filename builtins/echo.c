/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:42:24 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/13 15:11:04 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int ft_echo(t_minishell *mshell, t_token *token)
{
    int     newline = 1;
    char    *temp;
    
    token = token->next;
    if (token && token->input && ft_strncmp(token->input, "-n", 3) == 0)
	{
        newline = 0;
        token = token->next;
    }
    while(token) 
	{   
        handle_expansions(mshell, &token->input, 1);
        temp = handle_quotes(token->input, 0, 0);
        ft_putstr_fd(temp, STDOUT_FILENO);
        if (token->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
        free(temp);
		token = token->next;
    }
    if (newline)
	    ft_putstr_fd("\n", STDOUT_FILENO);
    return (0);
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
    t_token *token1 = cr_token(CMD, "echo");
	t_token *token2 = cr_token(ARG, "Ola,");
    t_token *token3 = cr_token(ARG, "\"\'$USER\'\"");
    t_token *token4 = cr_token(ARG, "\"   bom $?   \"");
    t_token *token5 = cr_token(ARG, "dia      ?");
	t_token *token6 = cr_token(ARG, "\' \"$PWD\" \'");

    // Conecte os tokens
    token1->next = token2;
    token2->next = token3;
	token3->next = token4;
    token4->next = token5;
	token5->next = token6;

    return token1; // Retorna o início da lista
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    init_struct(&mshell, envp);
    
    t_token *tokens = cr_sample_tokens();

    printf("Antes de echo:\n");
    t_token *temp = tokens;
    while (temp)
    {
        printf("Token type: %d, input:%s\n", temp->type, temp->input);
        temp = temp->next;
    }
    ft_echo(&mshell, tokens);
    clear_mshell(&mshell);
    free_tokens(tokens);
    
    return 0;
}*/

