/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:27:28 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 17:59:17 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DEF: Locates the first occurence of the null-terminated string little in the 
string big, where not more than len characters are sarched.
RETURN VALUE: If little is an empty string, big is returned; if little occurs
nowhere in big, NULL is returned; otherwise a pointer to the firstcharacter of 
the first occurence of little is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] != '\0' && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	str1[] = {"123456789"};
	char	str2[] = {"457"};
	size_t	len = ft_strlen(str1);

	printf("ft_strnstr %s\n", ft_strnstr(str1, str2, len));
}*/
