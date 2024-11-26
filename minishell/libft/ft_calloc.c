/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:45:35 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:51:32 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Allocates memory for an array of nmemb elements of size bytes each.
The allocated memory is filled with bytes of value zero.
RETURN VALUE: A pointer to the allocated memory.
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	tot_size;
	void	*dst;

	tot_size = nmemb * size;
	dst = malloc(tot_size);
	if (!dst)
		return (0);
	ft_memset(dst, 0, tot_size);
	return (dst);
}
