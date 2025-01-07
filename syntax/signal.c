/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:43:34 by sheila            #+#    #+#             */
/*   Updated: 2025/01/04 23:14:14 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_e_code = 130;
}

void	ft_sigint(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	g_e_code = 130;
}

void	ft_sigquit(int signal)
{
	(void)signal;
	ft_putstr_fd("", STDERR_FILENO);
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	g_e_code = 131;
}

void	ft_sigint_hd(int signal)
{
	
	if (signal == SIGINT)
	{
		g_e_code = 130;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_done = 1;
		ioctl(0,TIOCSTI, "");
		//clear_mshell((minishell(NULL)));
	}
}
