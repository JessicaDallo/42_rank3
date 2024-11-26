/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:47:35 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:51:37 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEF: Checks for an alphanumeric character
RETURN VALUE: Nonzero if the character c falls into the tested class, and 
zero if not. 
*/

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	char	teste = '5';
	int		resultado = ft_isalnum(teste);

	if (resultado == 1)
		printf("É Alfanumérico\n");
	else
		printf("Não é Alfanumérico\n");
	return (0);
}*/
