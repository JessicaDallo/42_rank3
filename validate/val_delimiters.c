/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_delimiters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:50:41 by jesilva-          #+#    #+#             */
/*   Updated: 2024/11/27 09:50:44 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	val_quot(char *arg, int *i)
{
	char	c;

	c = arg[*i];
	(*i)++;
	while (arg[*i])
	{
		if (arg[*i] == c)
		{
			if ((arg[*i] != '"' && arg[*i] != '\''))
				(*i)++;
			return (true);
		}
		(*i)++;
	}
	return (false);
}

bool	val_pipe(char *arg, int *was_cmd, int *i)
{
	if (!*was_cmd)
		return (false);
	(*i)++;
	*was_cmd = 0;
	while (arg[*i])
	{
		if (arg[*i] == '|')
			return (false);
		if (arg[*i] != ' ' && arg[*i] != '|')
			*was_cmd = 1;
		if (*was_cmd == 1)
			return (true);
		(*i)++;
	}
	return (*was_cmd);
}

bool	val_red(char *arg, int *was_cmd, int *i)
{
	int	was_red;

	was_red = 1;
	(*i)++;
	if (arg[*i] == '\0')
		return (false);
	*was_cmd = 0;
	while (arg[*i])
	{
		if (arg[*i] == '>')
		{
			was_red++;
			if (arg[*i - 1] == ' ')
				return (false);
		}
		if ((arg[*i] == '<' || arg[*i] == '|' || was_red > 2) && !(*was_cmd))
			return (false);
		else if (arg[*i] != ' ' && arg[*i] != '>')
			*was_cmd = 1;
		if (*was_cmd == 1)
			return (true);
		(*i)++;
	}
	return (*was_cmd);
}

bool	val_red_in(char *arg, int *was_cmd, int *i)
{
	int	was_red;

	was_red = 1;
	(*i)++;
	if (arg[*i] == '\0')
		return (false);
	*was_cmd = 0;
	while (arg[*i])
	{
		if (arg[*i] == '<')
		{
			was_red++;
			if (arg[*i - 1] == ' ')
				return (false);
		}
		if ((arg[*i] == '>' || arg[*i] == '|' || was_red > 2) && !(*was_cmd))
			return (false);
		else if (arg[*i] != ' ' && arg[*i] != '<')
			*was_cmd = 1;
		if (*was_cmd == 1)
			return (true);
		(*i)++;
	}
	return (*was_cmd);
}
