/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:55:09 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:55:18 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	
DEF: Returns a pointer to the last occurence of the character c in the string s. 
RETURN VALUE: A pointer to the matched character or NULL if the character
is not found. 
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (*s)
	{
		if (*(unsigned char *) s == (unsigned char) c)
			last = ((char *)s);
		s++;
	}
	if (*(unsigned char *) s == (unsigned char) c)
		return ((char *)s);
	return (last);
}
/*
int	main(void)
{
	char s[]= "";
	printf("Found last char em %s\n", ft_strrchr(s, 'o' + 256));
}*/
