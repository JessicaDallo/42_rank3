/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:21:55 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:53:06 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Outputs the string ’s’ to the given file descriptor followed by a newline.
RETURN VALUE: None.*/

#include "libft.h"

void	ft_putendl(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	write(1, s, len);
	write(1, "\n", 1);
}
