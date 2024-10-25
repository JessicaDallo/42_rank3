/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:48:20 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:51:52 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Checks for any printable character including space
RETURN VALUE: Nonzero if the character c falls into the tested class, and
zero if not.
*/

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	char	teste = '5';
	int		resultado = ft_isprint(teste);

	if (resultado == 1)
		printf("É imprimível\n");
	else
		printf("Não é imprimível\n");
	return (0);
}*/
