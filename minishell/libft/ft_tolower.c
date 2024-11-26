/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:55:23 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:55:42 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Converts uppercase letters to lowercase.
RETURN VALUE: The converted letter, or c if the conversion was not possible.
*/

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*
int	main(void)
{
	int	x = 'S';
	printf("Before: %i\n", x);
	printf("After: %i", ft_tolower(x));
	return (0);
}*/
