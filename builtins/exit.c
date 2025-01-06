/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:31:10 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/05 20:20:27 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void exit_mshell(t_minishell *mshell)
{
	if (mshell->e_code != 1)
	{
		close_pipes(mshell->commands);
		clear_mshell(mshell);
	}
}

int	get_exit(t_minishell *mshell, t_token *token)
{
	char *temp = handle_quotes(token->input, 0, 0);

	mshell->e_code = 0;
	if (!is_num(temp) || m_long(token->input))
	{
		error_msg("exit", "numeric argument required", 2);
		mshell->e_code = 2;
	}
	else if (token->next)
	{
		error_msg("exit", "too many arguments", 1);
		mshell->e_code = 1;
	}
	else if (token->input)
	{
		if (ft_atoi(temp) < 0)
			mshell->e_code = (256 + ft_atoi(temp));
		else
			mshell->e_code = ft_atoi(temp) % 256;
	}
	free(temp);
	temp = NULL;
	exit_mshell(mshell);
	return (mshell->e_code);
}

int	ft_exit(t_minishell *mshell, t_token *token)
{
	int	exit_code;

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
