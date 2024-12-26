/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:33:59 by sheila            #+#    #+#             */
/*   Updated: 2024/12/23 17:46:15 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/include_builtins.h"
 
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell mshell;

	char	*input = NULL;
	init_struct(&mshell, envp);
	while (1)
	{
		signal(SIGINT, ft_reset_prompt);
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
		if (val_sintax(input) > 0)
			continue ;
		mshell.commands = parse_input(input);
		if(mshell.commands)
			exec_cmd(&mshell);
			//is_builtin(&mshell, mshell.commands);
		free(input);
	}
}


