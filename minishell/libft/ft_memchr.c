/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:44:40 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:52:39 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Scans the initial n bytes of the memory area pointed to by s for the
first instance of c.
RETURN VALUE: A pointer to the matching byte or NULL if the character does
not occur in the given memory area.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*prt;
	size_t			x;

	prt = (unsigned char *)s;
	x = 0;
	while (x < n)
	{
		if (prt[x] == (unsigned char)c)
			return ((void *)s + x);
		x++;
	}
	return (NULL);
}

/*int	main(void)
{
	char str[] = "Hello, World!";
	printf ("String After (original): %s\n", memchr(str, ',', sizeof(str)));
	printf ("String After: %s\n", ft_memchr(str, ',', sizeof(str)));
}*/
