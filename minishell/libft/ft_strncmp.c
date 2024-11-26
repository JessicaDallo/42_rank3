/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:46:26 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:54:54 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Compares the first n bytes of s1 an s2.
RETURN VALUE: An integer less than, equal to, or greater than zero if s1
is found.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	else
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
/*
int	main(void)
{
	char	string1[] = "hello world";
	char	string2[] = "hello";
	int		size;

	size = 4;
	printf("%i\n", ft_strncmp(string1, string2, size));
	printf("%i", strncmp(string1, string2, size));
}*/
