/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:43:34 by sheila            #+#    #+#             */
/*   Updated: 2024/12/11 17:12:09 by shrodrig         ###   ########.fr       */
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
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	//mshell->e_code = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigint(int signal)
{
	t_minishell	*mshell;

	mshell = get_shell();
	if(signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(mshell->e_code = 130);
	}
}


void	ft_sigquit(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	//mshell->e_code  = 131;
}

/*void	ft_sigint_heredoc(int signal, t_minishell *mshell)
{
	if (signal == SIGINT)
	{
		mshell->e_code = 130;
		clear_mshell(mshell);
	}
}*/

//void	ft_receive_signal(void)
//{
//	struct sigaction	sig_int;
//	struct sigaction	sig_quit;

//	ft_memset(&sig_int, 0, sizeof(sig_int));
//	ft_memset(&sig_quit, 0, sizeof(sig_quit));
//	sig_int.sa_sigaction = ft_reset_prompt;
//	sig_quit.sa_handler = SIG_IGN;
//	sigaction(SIGINT, &sig_int, NULL);
//	sigaction(SIGQUIT, &sig_quit, NULL);
//}