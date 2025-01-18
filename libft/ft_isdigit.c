/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:48:11 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:51:48 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
LIBRARY: <ctype.h>
DEF: Checks for a digit (0 through 9)
RETURN VALUE: Nonzero if the character c falls into the tested class, and 
zero if not.
*/

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	char	teste = '5';
	int		resultado = ft_isdigit(teste);

	if (resultado == 1)
		printf("É um dígito\n");
	else
		printf("Não é um dígito\n");
	return (0);
}*/
