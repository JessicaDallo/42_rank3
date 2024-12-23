/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:16:30 by sheila            #+#    #+#             */
/*   Updated: 2024/12/23 18:01:46 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

char    *get_value(t_minishell *mshell, char *key)
{
    t_env   *temp;

    temp = mshell->env;
	while (temp != NULL)
    {
        if (ft_strcmp(temp->key, key) == 0)
			return(temp->value);
        temp = temp->next;
    }
    return(NULL);
}

void    update_env(t_minishell *mshell, char *key, char *value, bool flag)
{
    t_env   *temp;

    temp = mshell->env;
	while (temp != NULL)
    {
        if (ft_strcmp(temp->key, key) == 0)
        {
            if (flag)
            {
                temp->print = true;
			    free(temp->value);
                if(value)
	                temp->value = ft_strdup(value);
                else
                    temp->value = ft_strdup("");
            }
            break;
		}
        temp = temp->next;
	}
    if(!temp)
        add_env(mshell, key, value, flag);
    return;
}


void ft_export(t_minishell *mshell, t_token *tokens)
{
	char	**new_env;
    bool    flag;
    t_token   *temp;

    temp = tokens;
    temp = temp->next;
    if(!temp || !temp->input)
        print_export(mshell);
    else
    {
        while(temp)
        {
            flag = true;
            if (!ft_strchr(temp->input, '='))
                flag = false;
            new_env = ft_split(temp->input, '=');
	        if(!new_env)
	    	    return;
            update_env(mshell, new_env[0], new_env[1], flag);
            free_array(new_env);
            temp = temp->next;
        }
    }
}

