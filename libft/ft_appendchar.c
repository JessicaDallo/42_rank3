/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_appendchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:31:32 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 16:40:35 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_appendchar(char const *s1, char c)
{
	char			*newstr;
	unsigned int	i;

	newstr = (char *)malloc(strlen(s1) + 2);
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
