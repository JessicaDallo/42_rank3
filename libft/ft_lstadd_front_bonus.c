/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:53:43 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:52:09 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION: Adds the node ’new’ at the beginning of the list.
RETURN VALUE: None.*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}
/*int	main(void)
{
	t_list	*list = NULL;
	t_list	*lst1 = ft_lstnew("Element 1");
	t_list	*lst2 = ft_lstnew("Element 2");
	t_list	*lst3 = ft_lstnew("Element 3");
	t_list	*current;

	ft_lstadd_front(&list, lst3);
  ft_lstadd_front(&list, lst2);
  ft_lstadd_front(&list, lst1);

	current = list;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}*/