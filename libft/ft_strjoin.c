/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 08:54:26 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:53:41 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	
DEF: Allocates (with malloc) and returns a new string, which is the result of the
concatenation of s1 and s2.
RETURN VALUE: The new string. NULL if the allocation fails. 
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	j;

	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}
/*int	main(void)
{
	char	str1[] = "hello ";
	char	str2[]= "world";
	char	*strjoin = ft_strjoin(str1, str2);
	
	if (!strjoin)
		printf ("Error (NULL): ft_strjoin \n");
	else
		printf ("Concatenation of strings: %s\n", strjoin);
	
	free (strjoin);
	return (0);
}*/