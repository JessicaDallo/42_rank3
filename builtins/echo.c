/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:42:24 by shrodrig          #+#    #+#             */
/*   Updated: 2024/11/14 15:07:12 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int ft_echo(t_minishell *mshell)
{
    int newline = 1;
	int	i = 1;
    if (mshell->cmd->line[1] && ft_strncmp(mshell->cmd->line[1], "-n", 3) == 0)
	{
        newline = 0;
        i++;
    }
    while(mshell->cmd->line[i])
	{
        ft_putstr_fd(mshell->cmd->line[i], STDOUT_FILENO);
        if (mshell->cmd->line[i + 1])
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

