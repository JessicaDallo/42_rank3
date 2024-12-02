/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:31:10 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/01 14:06:29 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"


/*int	is_num(char *str)
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

int	get_exit(t_minishell *mshell)
{
	mshell->e_code = 0;
	if (mshell->token->value[0] != NULL)
	{
		error_msg("exit", "too many arguments\n");
		return(mshell->e_code = 1);
	}
    else if (!is_num(mshell->token->value[0]))
	{
		error_msg("exit", "numeric argument required");
		exit((mshell->e_code = 2));
	}
	else if (mshell->token->value[0])
    {
        if (is_num(mshell->token->value[0]) < 0)
			mshell->e_code = 256 + ft_atoi(mshell->token->value[0]);
		else
			mshell->e_code = ft_atoi(mshell->token->value[0]) % 256;
		exit(mshell->e_code);
    }
    else
        exit(mshell->e_code);
}

void	ft_exit(t_minishell *mshell)
{
	int	exit_code;

	//rl_clear_history();
	close_fds();
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_code = get_exit(mshell);
	clear_mshell(mshell);
	exit(exit_code);
	
}*/

/*int	main(int ac, char **av)
{
	if(ac > 2)
	{
		t_minishell	mshell;
		ft_bzero(&mshell, sizeof(mshell));
		mshell.token->line = av +1;
		ft_exit(&mshell);
	}
	return(0);
}*/