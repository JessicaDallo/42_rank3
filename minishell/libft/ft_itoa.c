/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 08:05:40 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:51:57 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  
DEF: Allocates (with malloc) and returns a string representing the integer
received as an argument. Negatives numbers must be handled. 
RETURN VALUE: The string representing the integer. NULL if the allocation
fails. 
*/

#include "libft.h"

static int	decimal(long n)
{
	int	size;

	size = 0;
	if (n <= 0)
	{
		n *= -1;
		size++;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char				*str;
	int					i;
	long int			num;

	num = n;
	i = decimal (num);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (num == 0)
		str[0] = '0';
	else if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		str[i--] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
/*
int	main(void)
{
	int n = 1036;
	char *itoa = ft_itoa(n);
	printf("%s\n\n", itoa);
}*/
