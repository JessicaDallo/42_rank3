/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:26:36 by sheila            #+#    #+#             */
/*   Updated: 2023/11/09 15:27:14 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DEF: Copies up to size - 1 characters from the NUL-terminated string src to 
dst, NUL-terminating the result.
RETURN VALUE: The length of src. 
*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	cont;
	size_t	i;

	i = 0;
	cont = 0;
	while (src[cont] != '\0')
		cont++;
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size -1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (cont);
}
/*
int	main(void)
{
	char		orig[] = "Hello";
	char		destiny[] = "Ola mundo";
	unsigned int	num;

	num = 3;
	num = ft_strlcpy(destiny, orig, num);
	printf("orig aft: %s\n dest aft: %s\n size aft: %d", orig, destiny, num);
}*/
