/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:11:37 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/29 14:26:24 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void    ft_env_reorder(char **keys, t_env *env)
{
    int		i;
	t_env	*temp;

	i = -1;
	while (keys[++i])
	{
		temp = env;
		while (temp)
		{
			if (!ft_strcmp(keys[i], temp->key))
			{
				if (temp->value && ft_strlen(temp->value) > 0)
					ft_printf("declare -x %s=\"%s\"\n",temp->key, temp->value);
				else
					ft_printf("declare -x %s=\"\"\n", temp->key);
				break;
			}
			temp = temp->next;
		}
	}
}

void ft_env_sorted(char **keys, int len)
{
    char    *aux;
    int     i;
    int     j;

    j = 1;
	while (j < len)
	{
		i = 0;
		while (i < len)
		{
			if (ft_strcmp(keys[j], keys[i]) < 0)
			{
				aux = keys[j];
				keys[j] = keys[i];
				keys[i] = aux;
			}
			i++;
		}
		j++;
	}    
}

void    print_export(t_minishell *mshell)
{
    char	**keys;
	t_env	*temp;
	int		i;

	i = 0;
	temp = mshell->env;
	keys = ft_calloc(sizeof(char *), (mshell->env_size + 1));
	while (temp)
	{
		keys[i++] = ft_strdup(temp->key);
		temp = temp->next;
	}
	ft_env_sorted(keys, mshell->env_size);
    ft_env_reorder(keys, mshell->env);
    free_array(keys);
}
//bool	check_key(t_minishell *mshell, char *input)
bool	check_key(char *input)
{
	int		i;

	i = 0;
	if (!ft_isalpha(input[i]) && input[i] != '_')
	{
		//mshell->e_code = 1;
		error_msg("export", "not a valid identifier", 1); //check if the exit code is correct
		return (false);
	}
	while (input[++i])
	{
		if (input[i] == '=')
			break ;
		if (!ft_isalnum(input[i]) && input[i] != '_')
		{
			//mshell->e_code = 1;
			error_msg("export", "not a valid identifier", 1); //check if the exit code is correct
			return (false);
		}
	}
	return (true);
}
