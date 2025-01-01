/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:43:34 by sheila            #+#    #+#             */
/*   Updated: 2025/01/01 23:43:27 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	handle_signal(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
}

void	ft_reset_prompt(int signal)
{
	t_minishell	**mshell;

	(void)signal;
	mshell = get_shell();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(*mshell)->e_code = 130;
}

void	ft_sigint(int signal)
{
	t_minishell	**mshell;

	mshell = get_shell();
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	(*mshell)->e_code = 130;
}

void	ft_sigquit(int signal)
{
	t_minishell	**mshell;

	(void)signal;
	mshell = get_shell();
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	(*mshell)->e_code  = 131;
}

void	ft_sigint_hd(int signal)
{
	t_minishell	**mshell;

	mshell = get_shell();
	if (signal == SIGINT)
	{
		(*mshell)->e_code = 130;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		clear_mshell((*mshell));
	}
}
