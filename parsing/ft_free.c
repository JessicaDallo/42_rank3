/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:33:03 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 15:33:03 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include_builtins.h"

void	ft_free_array(char **cmd)
{
	int	i;
	
	i = 0;
	if(!cmd)
		return ;
	while(cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	ft_free_token(t_token **token)
{
	t_token *temp;
	t_token *current;

	if(!token)
		return ;
	current = *token;
	while(current)
	{
		temp = current->next;
		free(current->value);
		current = temp;
	}
	*token = NULL;
}

// void	free_initial_array(char **initial)
// {
// 	int	i;

// 	i = 0;
// 	while (initial[i])
// 	{
// 		free(initial[i]);
// 		i++;
// 	}
// 	free(initial);
// }

// void	free_stack(t_node **stack)
// {
// 	t_node	*temp;
// 	t_node	*current;

// 	if (!stack)
// 		return ;
// 	current = *stack;
// 	while (current)
// 	{
// 		temp = current->next;
// 		free(current);
// 		current = temp;
// 	}
// 	*stack = NULL;
// }
