/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:20:19 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/01 23:11:28 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

/*int ft_pwd(t_minishell *mshell, t_token *token)
{
	char pwd[PATH_MAX];
	
	if(token->next)
	{
		if(ft_strncmp(token->next->input, "-", 1) == 0)
		{
			error_msg("pwd", "invalid options", 1);
			return (mshell->e_code = 1);
		}
	}
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		ft_putstr_fd(pwd, STDOUT_FILENO);
	else
		  perror_msg("pwd", "pwd");
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}*/

int ft_pwd(t_minishell *mshell, t_token *token)
{
	char *pwd;
	
	if(token->next)
	{
		if(ft_strncmp(token->next->input, "-", 1) == 0)
		{
			error_msg("pwd", "invalid options", 1);
			return (mshell->e_code = 1);
		}
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = get_value(mshell, "PWD");
		if (!pwd)
		{
			error_msg("pwd", "No such file or directory", 1);
			return(mshell->e_code = 1);
		}
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	if (pwd && pwd != get_value(mshell, "PWD"))
		free(pwd);
	return (0);
}
