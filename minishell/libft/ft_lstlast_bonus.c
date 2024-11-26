/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:52:26 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:52:23 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION: Returns the last node of the list.
RETURN VALUE: Last node of the list */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*int	main(void)
{
	t_list	*list1;
	t_list	*list2;
	t_list	*list3;
	t_list	*last;
	char		*lastcontent;

	list1 = ft_lstnew ("Hello");
	list2 = ft_lstnew ("World");
	list3 = ft_lstnew ("42");
	list1->next = list2;
	list2->next = list3;
	last = ft_lstlast(list1);
	lastcontent = last->content;

	printf("Last list: %s\n", lastcontent);
	return (0);
}*/