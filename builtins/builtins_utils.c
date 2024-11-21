/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:09:28 by sheila            #+#    #+#             */
/*   Updated: 2024/11/14 15:02:31 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	is_builtin(t_minishell *mshell, t_cmd *cmd)
{
	if(!mshell->cmd)
		return(0);
	else if (!(ft_strcmp(mshell->cmd->name, "cd")))
		return(ft_cd(mshell, cmd->line[0]), 1);
	else if (!(ft_strcmp(mshell->cmd->name, "echo")))
		return(ft_echo(mshell), 1);
	else if (!(ft_strcmp(mshell->cmd->name, "env")))
		return(ft_env(mshell->env), 1);
	else if (!(ft_strcmp(mshell->cmd->name, "exit")))
		return(ft_exit(mshell), 1);
	else if (!(ft_strcmp(mshell->cmd->name, "export")))
		return(ft_export(mshell, cmd->line), 1);
	else if (!(ft_strcmp(mshell->cmd->name, "pwd")))
		return(ft_pwd(), 1);
	else if (!(ft_strcmp(mshell->cmd->name, "unset")))
		return(ft_unset(mshell, cmd->line), 1);
	return(0);
}
