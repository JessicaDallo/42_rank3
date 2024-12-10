/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:12:41 by sheila            #+#    #+#             */
/*   Updated: 2024/12/10 15:04:05 by sheila           ###   ########.fr       */
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

void	free_tokens(t_token *tokens)
{
	t_token	*aux;
	
	while(tokens)
	{
		aux = tokens->next;
		if(tokens->input)
			free(tokens->input);
		free(tokens);
		tokens = aux;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*aux;
	
	while(cmd)
	{
		aux = cmd->next;
		if(cmd->tokens)
			free_tokens(cmd->tokens);
		free(cmd);
		cmd = aux;
	}
}

void	clear_mshell(t_minishell *mshell)
{
	if(!mshell)
		return;
	if(mshell->env)
		free_envlist(mshell->env);
	if(mshell->commands)
		free_cmd(mshell->commands);
	if(mshell->envp)
		free_array(mshell->envp);
	//close_fds();
	//exit(mshell->e_code);
	return;
}