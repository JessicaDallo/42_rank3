/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:09:28 by sheila            #+#    #+#             */
/*   Updated: 2024/10/29 16:05:39 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	perror_msg(char *cmd, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

char	*get_var(t_minishell *mshell, char *key)
{
    int i;

    i = -1;
	while (mshell->env.keys[++i])
	{
		if (ft_strcmp(mshell->env.keys[i], key) == 0)
			return (mshell->env.values[i]);
	}
	return (NULL);
}

int	is_builtin(t_minishell *mshell)
{
	if(!mshell->cmd)
		return(0);
	else if (!(ft_strcmp(mshell->cmd, "cd")))
		return(ft_cd(mshell, mshell->argv[0]), 1);
	else if (!(ft_strcmp(mshell->cmd, "echo")))
		return(ft_echo(mshell), 1);
	else if (!(ft_strcmp(mshell->cmd, "env")))
		return(ft_env(mshell->env), 1);
	else if (!(ft_strcmp(mshell->cmd, "exit")))
		return(ft_exit(mshell), 1);
	else if (!(ft_strcmp(mshell->cmd, "export")))
		return(ft_export(mshell, mshell->argv), 1);
	else if (!(ft_strcmp(mshell->cmd, "pwd")))
		return(ft_pwd(), 1);
	else if (!(ft_strcmp(mshell->cmd, "unset")))
		return(ft_unset(mshell, mshell->argv), 1);
	return(0);
}