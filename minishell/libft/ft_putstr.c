/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:57:47 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:53:15 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPION: Outputs the string ’s’ to the given file descriptor
RETURN VALUE: None.*/

#include "libft.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
	return ;
}
