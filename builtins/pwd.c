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

int ft_pwd(t_minishell *mshell, t_token *token)
{
	char pwd[PATH_MAX];
	
	if(token->next)
	{
		if(ft_strncmp(token->next->input, "-", 1) == 0)
		{
			error_msg("pwd", "invalid options", 1); //check if the exit code is correct
			return (mshell->e_code = 1);
		}
	}
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		ft_putstr_fd(pwd, STDOUT_FILENO);
	else
		  perror_msg("pwd", "pwd");
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
