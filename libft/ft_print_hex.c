/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:07:50 by shrodrig          #+#    #+#             */
/*   Updated: 2024/05/15 14:38:59 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhex(unsigned int n, const char c)
{
	char	*symbols;
	int		count;

	if (n >= 16)
	{
		count = ft_printhex(n / 16, c);
		return (count + ft_printhex(n % 16, c));
	}
	else
	{
		if (c == 'x')
			symbols = "0123456789abcdef";
		else
			symbols = "0123456789ABCDEF";
		return (ft_printchar(symbols[n]));
	}
}
