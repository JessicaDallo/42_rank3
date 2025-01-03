/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:42:24 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/01 23:00:09 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

bool	check_echo(t_token *token, bool *flag, int *newline)
{
	char    *str;

	str = token->input;
	str += 2;
	while(*str == 'n')
		str++;
	if(*str != '\0')
		*flag = false;
	else
		*newline = 0;
	return (*flag);
}

int	ft_echo(t_minishell *mshell, t_token *token)
{
	int		newline = 1;
	char	*temp;
	bool	flag;
	
	token = token->next;
	flag = true;
	while(token) 
	{
		if (token && token->input && flag && ft_strncmp(token->input, "-n", 2) == 0)
		{
			if(check_echo(token, &flag, &newline))
				token = token->next;
			continue;
		}
		handle_expansions(mshell, &token->input, 1);
		temp = handle_quotes(token->input, 0, 0);
		ft_putstr_fd(temp, STDOUT_FILENO);
		if (token->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		free(temp);
		token = token->next;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (mshell->e_code = 0);
}
