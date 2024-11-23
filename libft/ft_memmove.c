/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:41:38 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:52:52 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Copies n bytes from memory area src to memory area dst. The memory
**	areas may overlap.
RETURN VALUE: A pointer to dest.
*/
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;

	s = (char *)src;
	d = (char *)dest;
	if (!dest && !src)
		return (NULL);
	if (d > s)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	else
		ft_memcpy(d, s, n);
	return (dest);
}

/*int	main(void)
{
	char	src[] = "Hello World!";
	char	dest[30];
	int		n = 5;
	
	printf("Destiny (before): %s \n", dest);
	ft_memmove(dest, src, n);
	printf("Source: %s \n", src);
	printf("Destiny (after): %s", dest);
}*/
