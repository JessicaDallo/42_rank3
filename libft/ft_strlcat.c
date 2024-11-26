/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:28:39 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:53:49 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  
DEF: Appends the NUL-terminated string src to the end of dst. It will append at 
most size - strlen(dst) - 1 bytes, NUL-terminating the result.
RETURN VALUE: The initial length of dst plus the length of src.
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lenghts;
	size_t	i;
	size_t	lsrc;
	size_t	ldst;

	i = 0;
	lenghts = 0;
	lsrc = ft_strlen(src);
	ldst = ft_strlen(dst);
	if (size > ldst)
		lenghts = ldst + lsrc;
	else
		lenghts = lsrc + size;
	while (src[i] != '\0' && size > (ldst + 1))
	{
		dst[ldst] = src[i];
		ldst++;
		i++;
	}
	dst[ldst] = '\0';
	return (lenghts);
}

/*int	main(void)
{
	char		orig[] = "<3 Nino";
	char	destino[20] = "Luninha";
	unsigned int	nb = 14;

	nb = ft_strlcat(destino, orig, nb);
	printf("DEST +: %s\n nb:%i\n", destino, nb);
}*/
