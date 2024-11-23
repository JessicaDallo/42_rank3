/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:41:54 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:51:41 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DEF: Checks for an alphabetic character
RETURN VALUE: Nonzero if the character c falls into the tested class, and 
zero if not.*/

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	char	letra = 'A';
	int		resultado = ft_isalpha(letra);
	
	if (resultado == 1)
		printf("É uma letra\n");
	else
		printf("Não é uma letra\n");

	if (isalpha(letra))
		printf("É UMA LETRA\n");
	else
		printf("NÃO É UMA LETRA\n");
	return (0);
}*/
