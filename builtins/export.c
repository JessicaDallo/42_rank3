/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:16:30 by sheila            #+#    #+#             */
/*   Updated: 2024/11/07 18:20:12 by sheila           ###   ########.fr       */
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

void    update_env(t_minishell *mshell, char *key, char *value)
{
    t_env   *temp;

    temp = mshell->env;
	while (temp != NULL)
    {
        if (ft_strcmp(temp->key, key) == 0)
        {
			free(temp->value);
            if(value)
	            temp->value = ft_strdup(value);
            else
                temp->value = ft_strdup("");
            break;
		}
        temp = temp->next;
	}
    if(!temp)
        add_env(mshell, key, value);
    return;
}

void ft_export(t_minishell *mshell, char **line)
{
	char	**new_env;

    while(*line)
    {
        if (!*line)
            return;
        new_env = ft_split(*line, '=');
	    if(!new_env)
		    return;
        update_env(mshell, new_env[0], new_env[1]);
        free(new_env[0]);
        free(new_env[1]);
        free(new_env);
        line++;
    }
}

/*int main(int argc, char **argv, char **envp)
{
    t_minishell    mshell;
    t_env   *temp;

    init_struct(&mshell, envp);
    
    printf("\n--- Antes do export ---\n");
    
    temp = mshell.env;
    while (temp)
    {
        printf("%s = %s\n", temp->key, temp->value);
        temp = temp->next;
    }
    printf("\nSIZE_ENV = %d\n", mshell.env_size);
    if (argc > 1)
        ft_export(&mshell, ++argv);
    
    printf("\n--- Após o export ---\n");

    temp = mshell.env;
    while (temp)
    {
       printf("%s = %s\n", temp->key, temp->value);
       temp = temp->next;
    }
    printf("\nSIZE_ENV = %d\n", mshell.env_size);
    return 0;
}*/