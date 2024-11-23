/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:51:57 by sheila            #+#    #+#             */
/*   Updated: 2024/06/11 15:22:58 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	
DEF: Returns a pointer to the first occurence of the character c in the 
string s. 
RETURN VALUE: A pointer to the matched character or NULL if the character
is not found. 
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	x;

	x = ((unsigned char) c);
	while (*s && *s != x)
		s++;
	if (*s == x)
		return ((char *)s);
	else
		return (NULL);
}
/*int	main(void)
{
	char	str[] ="Hello World";
	int		i = 'l';
	
	ft_strchr(str, i);
	printf ("Location: %s",ft_strchr);
}*/
