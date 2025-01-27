/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:56:31 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/12 14:28:19 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_minishell *mshell, char *key)
{
	t_env	*temp;
	t_env	*aux;

	temp = mshell->env;
	aux = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (aux)
				aux->next = temp->next;
			else
				mshell->env = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			mshell->env_size--;
			return ;
		}
		aux = temp;
		temp = temp->next;
	}
}

void	ft_unset(t_minishell *mshell, t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	temp = temp->next;
	g_e_code = 0;
	while (temp)
	{
		if (!temp->input)
			return ;
		remove_env(mshell, temp->input);
		temp = temp->next;
	}
}
