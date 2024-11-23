/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:26:06 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:53:31 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  
DEF: Returns a pointer to a new string which is a duplicate of the string s.
RETURN VALUE: A pointer to the duplicated string. NULL if insufficient memory 
was available. 
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(s) + 1;
	dup = (char *)malloc(size);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, size);
	return (dup);
}

/*int	main(void)
{
	char	*test = ft_strdup("Hello World");
	printf("String dup: %s\n", test);
	
	free(test);
}*/
