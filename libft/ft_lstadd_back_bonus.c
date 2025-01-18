/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:13:07 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:52:05 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION: Adds the node ’new’ at the end of the list.
RETURN VALUE: None.*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = ft_lstlast(*lst);
	aux->next = new;
}
/*int	main(void)
{
	t_list	*list = NULL;
	t_list	*lst1 = ft_lstnew("Element 1");
	t_list	*lst2 = ft_lstnew("Element 2");
	t_list	*lst3 = ft_lstnew("Element 3");
	t_list	*current;

	ft_lstadd_back(&list, lst1);
  ft_lstadd_back(&list, lst2);
  ft_lstadd_back(&list, lst3);

	current = list;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}*/
