/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:09:28 by sheila            #+#    #+#             */
/*   Updated: 2024/11/23 17:58:17 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	is_builtin(t_minishell *mshell, t_token *token)
{
	if(!mshell->token)
		return(0);
	else if (!(ft_strcmp(mshell->token->name, "cd")))
		return(ft_cd(mshell, token->value[0]), 1);
	else if (!(ft_strcmp(mshell->token->name, "echo")))
		return(ft_echo(mshell), 1);
	else if (!(ft_strcmp(mshell->token->name, "env")))
		return(ft_env(mshell->env), 1);
	else if (!(ft_strcmp(mshell->token->name, "exit")))
		return(ft_exit(mshell), 1);
	else if (!(ft_strcmp(mshell->token->name, "export")))
		return(ft_export(mshell, token->value), 1);
	else if (!(ft_strcmp(mshell->token->name, "pwd")))
		return(ft_pwd(), 1);
	else if (!(ft_strcmp(mshell->token->name, "unset")))
		return(ft_unset(mshell, token->value), 1);
	return(0);
}


