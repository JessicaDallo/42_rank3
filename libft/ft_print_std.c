/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_std.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:07:59 by shrodrig          #+#    #+#             */
/*   Updated: 2024/05/15 14:38:45 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_printstr(char *str)
{
	int	len;

	if (!str)
		return (write (1, "(null)", 6));
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (len);
}

int	ft_printnbr(int c)
{
	char	*str;
	int		len;

	str = ft_itoa(c);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}

int	ft_printperc(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}
