/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:09:28 by sheila            #+#    #+#             */
/*   Updated: 2024/12/09 15:29:01 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

bool	is_builtin(t_cmd *commands)
{
	if(!commands || !commands->tokens)
		return(false);
	else if (!(ft_strcmp(commands->tokens->input, "cd")))
		return(true);
	else if (!(ft_strcmp(commands->tokens->input, "echo")))
		return(true);
	 else if (!(ft_strcmp(commands->tokens->input, "env")))
	 	return(true);
	else if (!(ft_strcmp(commands->tokens->input, "exit")))
		return(true);
	else if (!(ft_strcmp(commands->tokens->input, "export")))
		return(true);
	else if (!(ft_strcmp(commands->tokens->input, "pwd")))
		return(true);
	else if (!(ft_strcmp(commands->tokens->input, "unset")))
		return(true);
	return(false);
}
void	run_builtin(t_minishell *mshell, t_cmd *commands)
{
	if(!commands || !commands->tokens)
		return;
	else if (!(ft_strcmp(commands->tokens->input, "cd")))
		ft_cd(mshell, commands->tokens);
	else if (!(ft_strcmp(commands->tokens->input, "echo")))
		ft_echo(mshell, commands->tokens);
	 else if (!(ft_strcmp(commands->tokens->input, "env")))
	 	ft_env(mshell->env);
	else if (!(ft_strcmp(commands->tokens->input, "exit")))
		ft_exit(mshell, commands->tokens);
	else if (!(ft_strcmp(commands->tokens->input, "export")))
		ft_export(mshell, commands->tokens);
	else if (!(ft_strcmp(commands->tokens->input, "pwd")))
		ft_pwd();
	else if (!(ft_strcmp(commands->tokens->input, "unset")))
		ft_unset(mshell, commands->tokens);
	return;
}


