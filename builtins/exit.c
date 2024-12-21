/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:31:10 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/20 22:27:46 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	is_num(char *str)
{
    if(!str)
        return (0);
    else
    {
        if (*str == '-' || *str == '+')
		    str++;
	    while (*str)
	    {
	    	if (!(*str >= '0' && *str <= '9'))
	    		return (0);
	    	str++;
	    }
    }
	return (1);
}

int	get_exit(t_minishell *mshell, t_token *token)
{
	mshell->e_code = 0;
    
    if (!is_num(token->input))
    {
        error_msg("exit", "numeric argument required");
        return((mshell->e_code = 2));
    }
    else if (token->next)
    {
        error_msg("exit", "too many arguments");
        return(mshell->e_code = 1);
    }
    else if (token->input)
    {
        if (is_num(token->input) < 0)
            mshell->e_code = 256 + ft_atoi(token->input);
        else
            mshell->e_code = ft_atoi(token->input) % 256;
        return(mshell->e_code);
    }
    return(mshell->e_code);
}

//TRATAR DE ERROS NEGATIVOS 
//TRATAR DO EXIT'S CODES

int	ft_exit(t_minishell *mshell, t_token *token)
{
	int exit_code;
	
    token = token->next;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
    if (!token || !token->input)
        exit_code = 0;
    else
	    exit_code = get_exit(mshell, token);
	clear_mshell(mshell);
	exit(exit_code);
}

/*
//int	ft_exit(t_minishell *mshell, t_token *token)
// {
// 	int exit_code;
	
// 	ft_putstr_fd("exit\n", STDOUT_FILENO);
// 	exit_code = get_exit(mshell, token);
// 	printf("\nEXIT CODE: %d\n", mshell->e_code);
// 	clear_mshell(mshell);
// 	printf("\nEXIT CODE2: %d\n", exit_code);
// 	exit(exit_code);
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
    t_token *token1 = cr_token(CMD, "exit");
	t_token *token2 = cr_token(ARG, "300");
    //t_token *token3 = cr_token(ARG, "CDE");

    // Conecte os tokens
    token1->next = token2;
    //token2->next = token3;

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
   	ft_exit(&mshell, mshell.commands->tokens);
    printf("\nEXIT CODE: %d\n", mshell.e_code); 
    return 0;
}*/
