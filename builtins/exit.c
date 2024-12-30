/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:31:10 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/29 14:20:36 by sheila           ###   ########.fr       */
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
	
	//handle_quotes(token->input, 0, 0);
	//printf("token->input: %s\n", token->input);
	if (!is_num(handle_quotes(token->input, 0, 0)))
	{
		error_msg("exit", "numeric argument required", 2); //check if the exit code is correct
		return((mshell->e_code = 2));
	}
	else if (token->next)
	{
		error_msg("exit", "too many arguments", 1); //checkif the exit code is correct
		return(mshell->e_code = 1);
	}
	else if (token->input)
	{
		if (is_num(handle_quotes(token->input, 0, 0)) < 0)
			mshell->e_code = (256 + ft_atoi(handle_quotes(token->input, 0, 0)));
		else
			mshell->e_code = ft_atoi(handle_quotes(token->input, 0, 0)) % 256;
		return(mshell->e_code);
	}
	return(mshell->e_code);
}

//TRATAR DO EXIT'S CODES
int	ft_exit(t_minishell *mshell, t_token *token)
{
	int exit_code;
	
	token = token->next;
	if (!token || !token->input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit_code = 0;
		mshell->e_code = exit_code;
		clear_mshell(mshell);
	}
	else
	{
		exit_code = get_exit(mshell, token);
		mshell->e_code = exit_code;
	}
	return (exit_code);
}

