/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:42:24 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/23 15:38:50 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int ft_echo(t_minishell *mshell, t_token *token)
{
    int     newline = 1;
    char    *temp;
    
    token = token->next;
    while(token) 
	{   
        if (token && token->input && ft_strncmp(token->input, "-n", 2) == 0)
	    {
            newline = 0;
            token = token->next;
            continue;
        }
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
