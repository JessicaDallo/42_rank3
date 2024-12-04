/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:09:28 by sheila            #+#    #+#             */
/*   Updated: 2024/12/04 18:07:48 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	is_builtin(t_minishell *mshell, t_cmd *commands)
{
	if(!commands)
		return(0);
	else if (!(ft_strcmp(commands->tokens->input, "cd")))
		return(ft_cd(mshell, commands->tokens), 1);
	// else if (!(ft_strcmp(commands->tokens->input, "echo")))
	// 	//return(ft_echo(mshell), 1);
	// else if (!(ft_strcmp(commands->tokens->input, "env")))
	// 	//return(ft_env(mshell->env), 1);
	// else if (!(ft_strcmp(commands->tokens->input, "exit")))
	// 	//return(ft_exit(mshell), 1);
	// else if (!(ft_strcmp(commands->tokens->input, "export")))
	// 	//return(ft_export(), 1);
	// else if (!(ft_strcmp(commands->tokens->input, "pwd")))
	// 	//return(ft_pwd(), 1);
	// else if (!(ft_strcmp(commands->tokens->input, "unset")))
	// 	//return(ft_unset(mshell, token->value), 1);
	return(0);
}


