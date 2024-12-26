/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:31:10 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/23 15:39:17 by sheila           ###   ########.fr       */
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

