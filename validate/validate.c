/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:50:22 by jesilva-          #+#    #+#             */
/*   Updated: 2024/11/27 09:50:26 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include_builtins.h"

int	error_val_msg(char *str, t_minishell *mshell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	mshell->e_code = 2;
	return (1);
}

static int	ft_check_delimiters(char *arg, int *was_cmd, int *i, t_minishell *mshell)
{
	if (arg[*i] == '|')
	{
		if (!val_pipe(arg, was_cmd, i) || !was_cmd)
			return (error_val_msg("syntax error near unexpected token `|'", mshell));
	}
	if (arg[*i] == '>')
	{
		if (!val_red(arg, was_cmd, i))
			return (error_val_msg("syntax error near unexpected token  `>'", mshell));
	}
	if (arg[*i] == '<')
	{
		if (!val_red_in(arg, was_cmd, i))
			return (error_val_msg("syntax error near unexpected token  `<'", mshell));
	}
	if (arg[*i] == '"' || arg[*i] == '\'')
	{
		if (!val_quot(arg, i))
			return (error_val_msg("syntax error quote not closed", mshell));
	}
	return (0);
}

int	val_sintax(char *arg, t_minishell *mshell)
{
	int	was_cmd;
	int	i;

	i = 0;
	was_cmd = 0;
	if(!arg)
		return (1);
	while (arg[i])
	{
		if(!arg)
			return (1);
		if (ft_check_delimiters(arg, &was_cmd, &i, mshell))
			return (1);
		if (arg[i] != ' ')
			was_cmd = 1;
		if (arg[i] != '\0')
			i++;
		else
			break ;
	}
	return (0);
}
