/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:55:22 by sheila            #+#    #+#             */
/*   Updated: 2024/11/28 15:55:42 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include_builtins.h"

int	quote_count(char *arg, char c)
{
	int i;

	i= 0;
	i++;
	while (arg[i] != c)
	{
		i++;
	}
	i++;
	return (i);
}

bool	delimiter(char **arg)
{
	if (**arg == '|' || **arg == '>' || **arg == '<' || **arg == '\n')
	{
		if (*(*arg + 1 )== '<' || *(*arg) + 1 == '>')
			(*arg)++;
		return (true);
	}
	return (false);
}

void	quote_pointer(char **arg, char c)
{
	int i;
	
	i = 0;
	(*arg)++;
	while(**arg != c)
	{
		i++;
		(*arg)++;
	}
}