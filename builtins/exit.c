/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:31:10 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/01 23:01:03 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

static bool	ft_atol(char *str)
{
	long	signal;
	long	n;
	int i;

	i = 0;
	if (!ft_strcmp("-9223372036854775808", str))
		return (true);
	signal = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		signal = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	n = 0;
	while (ft_isdigit(str[i]))
	{
		if (n > n * 10 + (str[i] - '0'))
			return (false);
		n = n * 10 + (str[i] - '0');
		i++;
	}
	n = n * signal;
	return (true);
}

static bool	m_long(char *str)
{
	if(ft_atol(str))
		return (false);
	else
		return (true);
}

int	is_num(char *str)
{
	if(!str || !*str)
		return (0);
	else
	{
		if (*str == '-' || *str == '+')
			str++;
		while (*str)
		{
			if (!(*str >= '0' && *str <= '9') && *str != ' ' && !(*str >= 9 && *str <= 13))
				return (0);
			str++;
		}
	}
	return (1);
}

int	get_exit(t_minishell *mshell, t_token *token)
{
	mshell->e_code = 0;
	if (!is_num(handle_quotes(token->input, 0, 0)) || m_long(token->input))
	{
		error_msg("exit", "numeric argument required", 2);
		mshell->e_code = 2;
		clear_mshell(mshell);

	}
	else if (token->next)
	{
		error_msg("exit", "too many arguments", 1);
		return(mshell->e_code = 1);
	}
	else if (token->input)
	{
		if (ft_atoi(handle_quotes(token->input, 0, 0)) < 0)
			mshell->e_code = (256 + ft_atoi(handle_quotes(token->input, 0, 0)));
		else
			mshell->e_code = ft_atoi(handle_quotes(token->input, 0, 0)) % 256;
		clear_mshell(mshell);
	}
	return(mshell->e_code);
}

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

