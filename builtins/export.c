/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:16:30 by sheila            #+#    #+#             */
/*   Updated: 2025/01/05 19:53:24 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_minishell *mshell, char *key)
{
	t_env	*temp;

	temp = mshell->env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	update_env(t_minishell *mshell, char *key, char *value, bool flag)
{
	t_env	*temp;

	temp = mshell->env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (flag)
			{
				temp->print = true;
				free(temp->value);
				if (value)
					temp->value = ft_strdup(value);
				else
					temp->value = ft_strdup("");
			}
			break ;
		}
		temp = temp->next;
	}
	if (!temp)
		add_env(mshell, key, value, flag);
	return ;
}

bool	check_key(char *input)
{
	int		i;

	i = 0;
	if (!ft_isalpha(input[i]) && input[i] != '_')
	{
		error_msg("export", "not a valid identifier", 1);
		return (false);
	}
	while (input[++i])
	{
		if (input[i] == '=')
			break ;
		if (!ft_isalnum(input[i]) && input[i] != '_')
		{
			error_msg("export", "not a valid identifier", 1);
			return (false);
		}
	}
	return (true);
}

void	new_env(t_minishell *mshell, t_token *temp)
{
	char	**new_env;
	char	*clean_env;

	new_env = ft_split(temp->input, '=');
	clean_env = NULL;
	if (!new_env || !new_env[0])
		return ;
	handle_expansions(mshell, &new_env[1], 1);
	if (new_env[1])
	{
		clean_env = handle_quotes(new_env[1], 0, 0);
		update_env(mshell, new_env[0], clean_env, true);
	}
	else
		update_env(mshell, new_env[0], new_env[1], true);
	free_array(new_env);
	if (clean_env)
		free(clean_env);
}

void	ft_export(t_minishell *mshell, t_token *tokens)
{
	t_token	*temp;

	temp = tokens->next;
	if (!temp || !temp->input)
		print_export(mshell);
	else
	{
		while (temp)
		{
			if (!check_key(temp->input))
			{
				temp = temp->next;
				continue ;
			}
			if (!ft_strchr(temp->input, '='))
				update_env(mshell, temp->input, NULL, false);
			else
				new_env(mshell, temp);
			temp = temp->next;
		}
	}
}
