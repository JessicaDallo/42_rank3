/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:12:41 by sheila            #+#    #+#             */
/*   Updated: 2024/12/01 14:07:12 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	free_array(char **str) //env
{
	int	i;
	
	if(!str)
		return;
	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_envlist(t_env *env)
{
	t_env	*aux;

	while(env)
	{
		aux = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = aux;
	}
}

void	free_cmd(t_token *token)
{
	t_token	*aux;
	
	while(token)
	{
		aux = token->next;
		free(token->name);
		//free(token->type);
		free_array(token->value);
		free(token);
		token = aux;
	}
}

//void	clear_mshell(t_minishell *mshell)
//{
//	if(mshell->env)
//		free_envlist(mshell->env);
//	if(mshell->envp)
//		free_array(mshell->envp);
//	if(mshell->token)
//		free_cmd(mshell->token);
//}