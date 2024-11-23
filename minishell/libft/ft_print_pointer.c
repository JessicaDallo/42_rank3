/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:08:27 by shrodrig          #+#    #+#             */
/*   Updated: 2024/05/15 14:38:52 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counthex(unsigned long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	else
	{
		while (n)
		{
			count++;
			n /= 16;
		}
	}
	return (count);
}

void	ft_puthexa(unsigned long long n)
{
	char	*symbols;

	if (n >= 16)
	{
		ft_puthexa(n / 16);
		ft_puthexa(n % 16);
	}
	else
	{
		symbols = "0123456789abcdef";
		ft_printchar(symbols[n]);
	}
}

int	ft_printptr(unsigned long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len += ft_printstr("(nil)");
	else
	{
		ft_printstr("0x");
		ft_puthexa(n);
		len = 2 + ft_counthex(n);
	}
	return (len);
}
