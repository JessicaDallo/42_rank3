/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:19:04 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:51:19 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DEF: Erases the data in the n bytes of the memory starting at the location
pointed by s, by writing zeros ('\0') to that area.
RETURN VALUE: none
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *) s;
	while (i < n)
		str[i++] = '\0';
}
/*int main(void)
{
    char str[] = "Hello World";
    printf("Before: %s\n", str);
    ft_bzero(str, sizeof(str));
    printf("After: %s\n", str);
}*/
