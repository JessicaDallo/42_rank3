/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:37:11 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 14:30:10 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

/*int	open_quotes(char *str)
{
	int	quotes;
	quotes = 0;
	while(*str)
	{
		if(*str == '\'' || *str == '\"')
			quotes++;
		str++;
	}
	return((quotes % 2));
}
	

char	*check_syntax(char	**input)
{
	int i;
	i = -1;
	while(input[++i])
	{
		if(open_quotes(input[i]))
			ft_putstr_fd("You forgot some quote open\n", STDOUT_FILENO);
	}
}*/