/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:31:56 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:53:09 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Outputs the integer ’n’ to the given file descriptor.
RETURN VALUE: None.*/

#include "libft.h"

void	ft_putnbr(int n)
{
	long int	num;

	num = n;
	if (n < 0)
	{
		write(1, "-", 1);
		num *= -1;
	}
	else
		num = n;
	if (num >= 10)
		ft_putnbr(num / 10);
	ft_putchar((char)(num % 10 + '0'));
}
