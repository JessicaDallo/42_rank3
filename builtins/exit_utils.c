/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:50:22 by jesilva-          #+#    #+#             */
/*   Updated: 2025/01/05 19:50:22 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_atol(char *str)
{
	long	signal;
	long	n;
	int		i;

	i = 0;
	if (!ft_strcmp("-9223372036854775808", str))
		return (true);
	signal = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		signal = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	n = 0;
	while (ft_isdigit(str[i]))
	{
		if (n > n * 10 + (str[i] - '0'))
			return (false);
		n = n * 10 + (str[i] - '0');
		i++;
	}
	n = n * signal;
	return (true);
}

bool	m_long(char *str)
{
	if (ft_atol(str))
		return (false);
	else
		return (true);
}

int	is_num(char *str)
{
	if (!str || !*str)
		return (0);
	else
	{
		if (*str == '-' || *str == '+')
			str++;
		while (*str)
		{
			if (!(*str >= '0' && *str <= '9')
				&& *str != ' ' && !(*str >= 9 && *str <= 13))
				return (0);
			str++;
		}
	}
	return (1);
}