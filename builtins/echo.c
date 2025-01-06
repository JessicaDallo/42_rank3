/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:42:24 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/05 19:13:46 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_echo(t_token *token, bool *flag, int *newline)
{
	char	*str;

	str = token->input;
	str += 2;
	while (*str == 'n')
		str++;
	if (*str != '\0')
		*flag = false;
	else
		*newline = 0;
	return (*flag);
}

void	loop_echo(t_minishell *mshell, t_token *token, int *newline, bool *flag)
{
	char	*tmp;

	tmp = NULL;
	if (token && token->input && flag && !ft_strncmp(token->input, "-n", 2))
	{
		if (check_echo(token, flag, newline))
			return ;
	}
	handle_expansions(mshell, &token->input, 1);
	tmp = handle_quotes(token->input, 0, 0);
	ft_putstr_fd(tmp, STDOUT_FILENO);
	if (token->next)
		ft_putstr_fd(" ", STDOUT_FILENO);
	free(tmp);
}

int	ft_echo(t_minishell *mshell, t_token *token)
{
	int		newline;
	bool	flag;

	token = token->next;
	newline = 1;
	flag = true;
	while (token)
	{
		loop_echo(mshell, token, &newline, &flag);
		token = token->next;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (g_e_code = 0);
}

