/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:50 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:54:46 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Calculates the string pointed to by str, excluding terminating null byte.
RETURN VALUE: The number of bytes in the string pointed to by s.
*/

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*int	main(void)
{
	char *strin g= "hello world";
	int length= ft_strlen(string);
	
	printf("O comprimento da string é '%d'\n", length)
	printf("O comprimento da string é '%i'\n", ft_strlen(string));
    return 0;
}*/
