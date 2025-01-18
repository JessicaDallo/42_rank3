/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:50:07 by jesilva-          #+#    #+#             */
/*   Updated: 2024/12/26 17:50:12 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, size_t n)
{
	char	*dest;
	int		len;

	if (n > ft_strlen(s))
		len = ft_strlen(s);
	else
		len = n;
	dest = (char *)malloc(len * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strncpy(dest, s, n);
	dest[len] = '\0';
	return (dest);
}

// int main ()
// {
// 	char dst[] = "abcabcabc";
// 	printf ("%s deu?\n", ft_strndup(dst, 4, 6));
// 	printf("%s so dest\n", dst);
// 	return (0);
// }
