/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:56:31 by shrodrig          #+#    #+#             */
/*   Updated: 2024/11/07 18:33:27 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

//int	get_varname(char *key)
//{
//	while(*key)
//	{
//		if(!(ft_isalnum(key) || key == '_'))
//			return(1);
//		key++;
//	}
//	return(0);
//}

void    remove_env(t_minishell *mshell, char *key)
{
    t_env   *temp;
    t_env   *aux;

    temp = mshell->env;
    aux = NULL;
    while(temp)
    {
        if(ft_strcmp(temp->key, key) == 0)
        {
            if (aux)
                aux->next = temp->next;
            else
                mshell->env = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            mshell->env_size--;
            return;
        }
        aux = temp; 
        temp = temp->next; 
        }
}

void ft_unset(t_minishell *mshell, char **keys)
{
    while(*keys)
    {
        if (!*keys)
            return;
        remove_env(mshell, *keys);
        keys++;
    }
}

/*int main(int argc, char **argv, char **envp)
{
    t_minishell    mshell;
    t_env   *temp;

    init_struct(&mshell, envp);
    
    printf("\n--- Antes do unset ---\n");
    
    temp = mshell.env;
    while (temp)
    {
        printf("%s = %s\n", temp->key, temp->value);
        temp = temp->next;
    }
    printf("\nSIZE_ENV = %d\n", mshell.env_size);
    if (argc > 1)
        ft_unset(&mshell, ++argv);
    
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