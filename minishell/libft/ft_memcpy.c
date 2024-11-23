/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:33:15 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:52:46 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Copies n bytes from memory area src to memory area dest. The memory 
area must not overlap.
RETURN VALUE: Returns a pointer to dest. 
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	x;
	char			*d;
	const char		*s;

	x = 0;
	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (x < n)
	{
		d[x] = s[x];
		x++;
	}
	return (dest);
}

/*int	main(void)
{
	char    src[] = "Hello World!";
	char    dest[20];
	int     n = sizeof(src);

	ft_memcpy(dest, src, n);
	printf("Source: %s \n", src);
	printf("Destiny: %s", dest);
}*/
