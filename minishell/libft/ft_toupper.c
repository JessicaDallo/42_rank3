/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:31:53 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:55:47 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Converts lowercase letters to uppercases.
RETURN VALUE: The converted letter or c, if conversion is not possible.
*/

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*
int	main(void)
{
	int	x = 's';
	printf("Before: %i \n", x);
	ft_toupper(x);
	printf("After: %i",ft_toupper(x));
}*/
