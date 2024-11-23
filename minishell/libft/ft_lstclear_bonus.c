/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:40:13 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 19:04:43 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION: Deletes and frees the given node and every successor of that
node, using the function ’del’ and free(3). Finally, the pointer to the list
must be set to NULL.
RETURN VALUE: None.*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = aux;
	}
	*lst = NULL;
}
