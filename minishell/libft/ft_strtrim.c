/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:59:35 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:55:26 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	
DEF: Allocates (with malloc) and returns a copy of s1 with the characters
specified in 'set' removed from the beginning and the end of the string.
RETURN VALUE: The trimmed string or NULL, if the allocation fails.
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	char		*dest;

	if (!s1 || !set)
		return (NULL);
	i = ft_strlen(s1);
	j = 0;
	while (s1[j] && ft_strchr(set, s1[j]))
		j++;
	while (i > 0 && ft_strchr(set, s1[i - 1]))
		i--;
	dest = ft_substr(s1, j, i - j);
	if (!dest)
		return (0);
	return (dest);
}
/*
int	main(void)
{
	printf("%s\n", ft_strtrim("lorem ipsum dolor sit amet\n", "tel"));
	return (0);
}*/
