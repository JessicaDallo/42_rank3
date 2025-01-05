/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:33:59 by sheila            #+#    #+#             */
/*   Updated: 2025/01/05 00:18:43 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_signal(void)
{
	signal(SIGINT, ft_reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}
//void	read_input(t_minishell *mshell, char *input)
//{
//}

void	main_exec(t_minishell mshell, char *input)
{
	mshell.commands = parse_input(input);
	if (mshell.commands)
		handle_exec(&mshell);
	if (mshell.commands)
	{
		free_cmd(mshell.commands);
		mshell.commands = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mshell;
	char		*input;

	(void)argc;
	(void)argv;
	input = NULL;
	init_struct(&mshell, envp);
	while (1)
	{
		handle_signal();
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit_main\n");
			break ;
		}
		if (*input == '\0')
			continue ;
		if (*input)
			add_history(input);
		if (val_sintax(input, &mshell) > 0)
			continue ;
		main_exec(mshell, input);
		free(input);
	}
	//clear_mshell(&mshell);
}

/*int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell mshell;
	char		*input;

	input = NULL;
	init_struct(&mshell, envp);
	while (1)
	{
		signal(SIGINT, ft_reset_prompt);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit_main\n");
			break;
		}
		if(*input == '\0')
			continue ;
		if(*input)
			add_history(input);
		if (val_sintax(input, &mshell) > 0)
			continue ;
		mshell.commands = parse_input(input);
		if(mshell.commands)
			handle_exec(&mshell);
		if(mshell.commands)
		{
		  	free_cmd(mshell.commands);
				mshell.commands = NULL;
		}
		free(input);
	}
}*/

//mais de 25 linhas
