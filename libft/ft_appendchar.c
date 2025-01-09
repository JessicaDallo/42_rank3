/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_appendchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:31:32 by sheila            #+#    #+#             */
/*   Updated: 2025/01/04 19:27:12 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_appendchar(char const *s1, char c)
{
	char			*newstr;
	unsigned int	i;

	newstr = (char *)malloc(ft_strlen(s1) + 2);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	return (newstr);
}

/*int	main(void)
{
	char	str1[] = "hell";
	char	c= 'o';
	char	*appchar = ft_appendchar(str1, c);
	
	if (!appchar)
		printf ("Error (NULL): ft_appendchar \n");
	else
		printf ("Append char to string: %s\n", appchar);
	
	free (appchar);
	return (0);
}*/
