/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:44:12 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 14:44:12 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, size_t n)
{
	char	*dest;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strnlen(s, n);
	dest = (char *)malloc(len * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strncpy(dest, s, n);
	return (dest);
}

// int main ()
// {
// 	char dst[] = "abcabcabc";
// 	printf ("%s deu?\n", ft_strndup(dst, 4, 6));
// 	printf("%s so dest\n", dst);
// 	return (0);
// }