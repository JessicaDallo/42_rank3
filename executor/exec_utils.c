/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 01:55:14 by sheila            #+#    #+#             */
/*   Updated: 2025/01/09 02:19:53 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_ncmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	wait_childs(t_minishell *mshell, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds)
	{
		waitpid(mshell->child[i], &g_e_code, 0);
		i++;
	}
}

void	check_execve(t_minishell *mshell, char **args)
{
	char	*executable;

	executable = get_execpath(mshell, args[0], -1);
	if (!executable)
	{
		check_execpath(args[0], executable);
		free_array(args);
		clear_mshell(mshell);
	}
	if (execve(executable, args, mshell->envp))
		check_execpath(args[0], executable);
	free(executable);
	free_array(args);
}
