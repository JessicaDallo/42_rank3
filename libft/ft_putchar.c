/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:20:25 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:53:02 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION: Outputs the character ’c’ to the given file descriptor.
RETURN VALUE: None.*/

#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
