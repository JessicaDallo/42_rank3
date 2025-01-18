/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:18:59 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:52:34 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION: Counts the number of nodes in a list.
RETURN VALUE: The length of the list.*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
/*int	main(void)
{
	t_list	*list1;
	t_list	*list2;
	t_list	*list3;

	list1 = ft_lstnew ("Hello");
	list2 = ft_lstnew ("World");
	list3 = ft_lstnew ("42");
	list1->next = list2;
	list2->next = list3;
	printf("Size list: %d\n", ft_lstsize(list1));
	while (list1 != NULL)
	{
		printf("%s\n", (char *)list1->content);
		list1 = list1->next;
	}
	return (0);
}*/
