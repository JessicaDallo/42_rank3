/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:30:42 by sheila            #+#    #+#             */
/*   Updated: 2025/01/04 19:27:18 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>

int	ft_atoi_base(const char *str, int str_base)
{
	if (str_base < 2 || str_base > 16)
		return (0);
	int result = 0;
	int signal = 1;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signal = -1;
		str++;
	}

	while (*str)
	{
		int digit = 0;
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			digit = *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			digit = *str - 'A' + 10;
		else
			break;
		if (digit >= str_base)
			break;
		result = result * str_base + digit;
		str++;
	}
	return (signal * result);
}

int	main(void)
{
	printf("%d\n", ft_atoi_base("a", 16));
	printf("%d\n", ft_atoi_base("1a3F", 16));
	printf("%d\n", ft_atoi_base("12fdb3", 16));
	printf("%d\n", ft_atoi_base("12FDB3", 16));
	printf("%d\n", ft_atoi_base("1010", 2));
	printf("%d\n", ft_atoi_base("0", 10));
	printf("%d\n", ft_atoi_base("-42", 10));
	printf("%d\n", ft_atoi_base("42", 10));
	printf("%d\n", ft_atoi_base("-2147483648", 10));
}*/