/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:31:10 by shrodrig          #+#    #+#             */
/*   Updated: 2024/10/22 13:56:53 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"


int	is_num(char *str)
{
    if(!str)
        return (0);
    else
    {
	    while (*str)
	    {
	    	if (!(*str >= '0' && *str <= '9'))
	    		return (0);
	    	str++;
	    }
    }
	return (1);
}

int	ft_exit(t_minishell *mshell)
{
	mshell->e_code = 0;
	if (mshell->argv[1] && mshell->argv[2] != NULL)
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", STDOUT_FILENO);
		return(mshell->e_code = 1);
	}
    else if (mshell->argv[1] && !is_num(mshell->argv[1]))
	{
		ft_putstr_fd("exit: numeric argument required", STDOUT_FILENO);
		exit((mshell->e_code = 2));
	}
	else if (mshell->argv[1])
    {
        if (is_num(mshell->argv[1]) < 0)
			mshell->e_code = 256 + ft_atoi(mshell->argv[1]);
		else
			mshell->e_code = ft_atoi(mshell->argv[1]) % 256;
		exit(mshell->e_code);
    }
    else
        exit(mshell->e_code);
}

/*int	main(int ac, char **av)
{
	if(ac > 2)
	{
		t_minishell	mshell;
		ft_bzero(&mshell, sizeof(mshell));
		mshell.argv = av +1;
		ft_exit(&mshell);
	}
	return(0);
}*/