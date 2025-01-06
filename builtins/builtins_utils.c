/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:09:28 by sheila            #+#    #+#             */
/*   Updated: 2025/01/04 22:57:24 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_options(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if ((ft_strcmp(temp->input, "echo")))
		g_e_code = 0;
	if (!(ft_strcmp(temp->input, "unset")) || !(ft_strcmp(temp->input, "env")) \
		|| !(ft_strcmp(temp->input, "export")))
	{
		if (!temp->next)
			return (false);
		temp = temp->next;
		if (ft_strncmp(temp->input, "-", 1) == 0)
		{
			g_e_code = 1;
			error_msg(tokens->input, "no support for options", 1);
			return (true);
		}
	}
	return (false);
}

int	is_builtin(t_minishell *mshell, t_cmd *commands)
{
	if (!commands || !commands->tokens)
		return (0);
	if (!check_options(commands->tokens))
	{
		if (!(ft_strcmp(commands->tokens->input, "cd")))
			return (ft_cd(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "echo")))
			return (ft_echo(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "env")))
			return (ft_env(mshell->env), 1);
		else if (!(ft_strcmp(commands->tokens->input, "exit")))
			return (ft_exit(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "export")))
			return (ft_export(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "pwd")))
			return (ft_pwd(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "unset")))
			return (ft_unset(mshell, commands->tokens), 1);
	}
	return (0);
}
