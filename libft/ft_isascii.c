/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:47:48 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:51:44 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Checks wheter c is a 7-bit unsigned char value that fits into the ASCII 
character set.
RETURN VALUE: Nonzero if the character c falls into the tested class, and 
zero if not. 
*/

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	char	teste = '5';
	int		resultado = ft_isascii(teste);
	if (resultado == 1)
		printf("Está na ASCII\n");
	else
		printf("Não está na ASCII");
	return (0);
}*/
