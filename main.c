/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:33:59 by sheila            #+#    #+#             */
/*   Updated: 2024/11/22 16:43:34 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/include_builtins.h"

/*int main(int argc, char **argv, char **envp)
{
    t_minishell mshell;
	
    (void)argc;
    init_struct(&mshell, envp);
    check_syntax(argv);
   
   return 0;
}

int main (int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell mshell;
	char	*input = NULL;
	
	init_struct(&mshell, envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if(*input)
			add_history(input);

		//printf("%s\n", input);
		
		if (validate(&input) > 0)
			continue;
		get_tokens(input);
		//get_tokens(input);
		//t_token **tokens = tokenize(const char *input)
	}
	
}*/

