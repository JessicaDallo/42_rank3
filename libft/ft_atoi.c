/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:51:04 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:51:08 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DEF: Converts the inicial portion of the string pointed to by nptr to int.
RETURN VALUE: The converted value.*/

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		sin;
	int		result;
	int		i;

	sin = 1;
	i = 0;
	result = 0;
	while (nptr[i] == 32 || (nptr [i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sin = sin * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sin);
}
/*int     main (void)
{
        char    teste[] = "   ---+--+123ab123";

        printf("ft_atoi: %i\n", ft_atoi(teste));
        printf("atoi: %i", atoi(teste));
}*/