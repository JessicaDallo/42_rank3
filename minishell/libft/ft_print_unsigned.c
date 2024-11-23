/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:08:15 by shrodrig          #+#    #+#             */
/*   Updated: 2024/06/11 17:48:52 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nlen(unsigned int n, unsigned int base)
{
	int	count;

	count = 0;
	while (n)
	{
		count++;
		n /= base;
	}
	return (count);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		i;

	i = ft_nlen(n, 10);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (n)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int	print_uint(unsigned int n)
{
	char	*nbr;
	int		x;

	if (n == 0)
	{
		ft_printchar('0');
		return (1);
	}
	else
	{
		nbr = ft_uitoa(n);
		x = ft_printstr(nbr);
		free (nbr);
	}
	return (x);
}
