/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:14:36 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:52:43 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Compares the first n bytes of the memory areas s1 and s2.
RETURN VALUES: An integer less than, equal to, or greater than zero if the
first n bytes of s1 is found.
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_memcmp("Hello World", "Hello World", 7));
	printf("%d\n", memcmp("Hello World", "Hello World", 7));
	printf("%d\n", ft_memcmp("Hello World", "HeLlo World", 5));
	printf("%d\n", memcmp("Hello World", "HeLlo World", 5));
	printf("%d\n", ft_memcmp("Hello World", "HellO woRlD", 3));
	printf("%d\n", memcmp("Hello World", "HellO woRlD", 3));
}*/
