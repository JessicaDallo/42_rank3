/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:42:24 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/03 20:06:39 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int ft_echo(t_minishell *mshell)
{
    int     newline = 1;
	int     i = 1;
    char    *str;
    
    if (mshell->tokens->value[0] && ft_strncmp(mshell->tokens->value[0], "-n", 3) == 0)
	{
        newline = 0;
        i++;
    }
    while(mshell->tokens->value[i]) 
	{
        handle_expansions(mshell, &mshell->tokens->value[i], 0);
        str = handle_quotes(mshell->tokens->value[i], 0, 0);
        ft_putstr_fd(str, STDOUT_FILENO);
        if (mshell->tokens->value[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
    }
    if (newline)
	    ft_putstr_fd("\n", STDOUT_FILENO);
    return (0);
}

/*int main(int argc, char **line)
{
	(void)argc;
    t_minishell mshell;
    ft_bzero(&mshell, sizeof(mshell));
    line++;
	mshell.line = line;
    ft_echo(&mshell);
	return(0);
}*/

