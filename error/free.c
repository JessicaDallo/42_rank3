/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:12:41 by sheila            #+#    #+#             */
/*   Updated: 2025/01/03 00:09:25 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	free_array(char **str)
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
	printf("free_tokens entrou\n");
	while(tokens)
	{
		aux = tokens->next;
		if(tokens->input)
			free(tokens->input);
		free(tokens);
		tokens = aux;
	}
	//tokens = NULL;
	printf("free_tokens_saiu\n");
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*aux;
	printf("free_cmd entrou\n");
	if(!cmd)
		return;
	while(cmd)
	{
		aux = cmd->next;
		if(cmd->tokens)
			free_tokens(cmd->tokens);
		free(cmd);
		cmd = aux;
	}
	//cmd = NULL;
	printf("free_cmd saiu\n");
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
	close(mshell->heredoc_fd);
	close_fds();
	exit(mshell->e_code);
}
