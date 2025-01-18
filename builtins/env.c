/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:56:58 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/09 01:24:02 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env, t_token *tokens)
{
	t_env	*temp;

	temp = env;
	if (tokens->next)
	{
		g_e_code = 1;
		error_msg(tokens->input, "arguments or options aren't supported", 1);
		return ;
	}
	while (temp != NULL)
	{
		if (temp->print)
		{
			ft_putstr_fd(temp->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(temp->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		temp = temp->next;
	}
	g_e_code = 0;
}

void	add_env(t_minishell *mshell, char *key, char *value, bool flag)
{
	t_env	*temp;
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	if (value != NULL)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->print = flag;
	new_node->next = NULL;
	if (mshell->env == NULL)
		mshell->env = new_node;
	else
	{
		temp = mshell->env;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	mshell->env_size++;
}

void	init_env(t_minishell *mshell)
{
	char	**key;
	char	*value;
	int		i;

	i = 0;
	mshell->env = NULL;
	while (mshell->envp[i])
	{
		key = ft_split(mshell->envp[i], '=');
		value = ft_strdup(ft_strchr(mshell->envp[i], '=') + 1);
		if (key[0] != NULL)
			add_env(mshell, key[0], value, true);
		if (value)
			free(value);
		free_array(key);
		i++;
	}
}

void	init_struct(t_minishell *mshell, char **envp)
{
	int	i;

	ft_bzero(mshell, sizeof(t_minishell));
	if (!mshell)
		return ;
	i = 0;
	while (envp[i])
		i++;
	mshell->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!mshell->envp)
		return ;
	i = 0;
	while (envp[i])
	{
		mshell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	mshell->envp[i] = NULL;
	init_env(mshell);
}
