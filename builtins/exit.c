/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:31:10 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/04 22:58:27 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exit_mshell(t_minishell *mshell)
{
	if (g_e_code != 1)
	{
		close_pipes(mshell->commands);
		clear_mshell(mshell);
	}
}

int	get_exit(t_minishell *mshell, t_token *token)
{
	char *temp = handle_quotes(token->input, 0, 0);

	g_e_code = 0;
	if (!is_num(temp) || m_long(token->input))
	{
		error_msg("exit", "numeric argument required", 2);
		g_e_code = 2;
	}
	else if (token->next)
	{
		error_msg("exit", "too many arguments", 1);
		g_e_code = 1;
	}
	else if (token->input)
	{
		if (ft_atoi(temp) < 0)
			g_e_code = (256 + ft_atoi(temp));
		else
			g_e_code = ft_atoi(temp) % 256;
	}
	free(temp);
	temp = NULL;
	exit_mshell(mshell);
	return (g_e_code);
}

int	ft_exit(t_minishell *mshell, t_token *token)
{
	int	exit_code;

	token = token->next;
	if (!token || !token->input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit_code = 0;
		g_e_code = exit_code;
		clear_mshell(mshell);
	}
	else
	{
		exit_code = get_exit(mshell, token);
		g_e_code = exit_code;
	}
	return (exit_code);
}
