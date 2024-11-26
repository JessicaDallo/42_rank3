/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:07:22 by shrodrig          #+#    #+#             */
/*   Updated: 2023/11/01 18:52:31 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION: Allocates (with malloc(3)) and returns a new node. The member
variable ’content’ is initialized with the value of the parameter ’content’.
The variable ’next’ is initialized to NULL.
RETURN VALUE: None.*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*int main (void)
{
	char	str[] = "Hello World";
	t_list	*str2;

	str2 = ft_lstnew((void *)str);
	printf("String: %s\n", str);
	printf("*ft_lstnew: %s\n", str2->content);
}*/