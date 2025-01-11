/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:33:59 by sheila            #+#    #+#             */
/*   Updated: 2025/01/09 02:23:45 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_e_code;

void	handle_signal_main(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_reset_prompt);
}

void	main_exec(t_minishell *mshell, char *input)
{
	mshell->commands = parse_input(input);
	if (mshell->commands)
		handle_exec(mshell);
	if (mshell->commands)
	{
		free_cmd(mshell->commands);
		mshell->commands = NULL;
	}
}

void	read_input(t_minishell mshell)
{
	char	*input;

	input = NULL;
	while (1)
	{
		handle_signal_main();
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input == '\0')
			continue ;
		if (*input)
			add_history(input);
		if (val_sintax(input) > 0)
			continue ;
		main_exec(&mshell, input);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mshell;

	if (argc > 1)
		error_msg(*argv, "too many arguments", 2);
	else
	{
		init_struct(&mshell, envp);
		g_e_code = 0;
		read_input(mshell);
		clear_mshell(&mshell);
	}
}
