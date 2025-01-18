/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:39:18 by sheila            #+#    #+#             */
/*   Updated: 2023/11/01 18:52:16 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION: Takes as a parameter a node and frees the memory of the node’s
content using the function ’del’ given as a parameter and free the node.
The memory of’next’ must not be freed.
RETURN VALUE: None.*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*void	del_content(void *content)
{
	content = NULL;
}

int main(void)
{
	t_list *list1 = malloc(sizeof(t_list));
	t_list *list2 = malloc(sizeof(t_list));
	t_list *list3 = malloc(sizeof(t_list));

	if (list1 == NULL || list2 == NULL || list3 == NULL)
		return 1;

	list1->content = "Hello";
	list2->content = "World";
	list3->content = "42";

	list1->next = list2;
	list2->next = list3;
	list3->next = NULL;
	while (list1 != NULL)
	{
		printf("%s\n", (char *)list1->content);
		list1 = list1->next;
	}
	ft_lstdelone(list1, &del_content);
	ft_lstdelone(list2, &del_content);
	ft_lstdelone(list3, &del_content);
	if (list1 == NULL && list2 == NULL && list3 == NULL )
		printf("DONE\n");
	return (0);
}*/