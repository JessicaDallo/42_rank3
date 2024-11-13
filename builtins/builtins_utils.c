/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:09:28 by sheila            #+#    #+#             */
/*   Updated: 2024/11/13 17:45:02 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	is_builtin(t_minishell *mshell)
{
	if(!mshell->cmd)
		return(0);
	else if (!(ft_strcmp(mshell->cmd, "cd")))
		return(ft_cd(mshell, mshell->line[0]), 1);
	else if (!(ft_strcmp(mshell->cmd, "echo")))
		return(ft_echo(mshell), 1);
	else if (!(ft_strcmp(mshell->cmd, "env")))
		return(ft_env(mshell->env), 1);
	else if (!(ft_strcmp(mshell->cmd, "exit")))
		return(ft_exit(mshell), 1);
	else if (!(ft_strcmp(mshell->cmd, "export")))
		return(ft_export(mshell, mshell->line), 1);
	else if (!(ft_strcmp(mshell->cmd, "pwd")))
		return(ft_pwd(), 1);
	else if (!(ft_strcmp(mshell->cmd, "unset")))
		return(ft_unset(mshell, mshell->line), 1);
	return(0);
}
