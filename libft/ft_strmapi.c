/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:17:01 by sheila            #+#    #+#             */
/*   Updated: 2023/11/09 15:36:12 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  
DEF: Applies the function 'f' to each character of the string 's', and 
passing its index as first argument to create a new string (with malloc) 
resulting from successive applications of 'f'
RETURN VALUE: The string created from the successive applications of 'f'. 
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	if (!s || !f)
		return (NULL);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
