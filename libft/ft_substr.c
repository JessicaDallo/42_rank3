/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:32:58 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:55:31 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Allocates (with malloc) and returns a substring from string 's'. The
substring begins at index 'start' and is of maximum size 'len'.
RETURN VALUE: The substring. NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		dest = malloc(1);
		dest[0] = '\0';
		return (dest);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (j < len && i < (ft_strlen (s)))
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char	*test;

	test = ft_substr("Hello World", 1, 4);
	printf("Substr: %s\n", test);
}*/
