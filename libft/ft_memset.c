/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:47:21 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:52:57 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Fills the first n bytes of the memory area pointed to by s with the
constant byte c.
RETURN VALUE: Returns a pointer to the memory area s.
*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *) s;
	while (i < n)
		str[i++] = c;
	return (s);
}

/*int	main(void)
{
	int		x = 'a';
	size_t	n = 3;
	char	s[] = "Hello world";

	printf("Before: %s\n", s);
	//ft_memset(s, x, n);
	////printf("After: %s\n", s);
	memset(s, x, n);
	printf("Original: %s\n", s);
}*/
