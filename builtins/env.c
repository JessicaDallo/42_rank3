/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:56:58 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/06 18:49:18 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void    ft_env(t_env *env)
{
    t_env   *temp;
    
    temp = env;
    while(temp != NULL)
    {
        ft_putstr_fd(temp->key, STDOUT_FILENO);
        ft_putstr_fd("=", STDOUT_FILENO);
        ft_putstr_fd(temp->value, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        temp = temp->next;
    }
    return;
}

void    add_env(t_minishell *mshell, char *key, char *value)
{
    t_env   *temp;
    t_env   *new_node;

    new_node = (t_env *)malloc(sizeof(t_env));
    if(!new_node)
        return;
    new_node->key = ft_strdup(key); //key = ft_strjoin("=", key[1]); para adicionar o '=' de volta
	if (value != NULL)
        new_node->value = ft_strdup(value);
    else
        new_node->value = ft_strdup("");
    new_node->next = NULL;
    if(mshell->env == NULL)
        mshell->env = new_node;
    else
    {
        temp = mshell->env;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
    mshell->env_size++;
}

void    init_struct(t_minishell *mshell, char **envp)
{
    char    **key;
    int         i;
    
    ft_bzero(mshell, sizeof(t_minishell));
    if(!mshell)
        return;
    i = 0;
    mshell->env = NULL;
    while(envp[i])
    {
        key = ft_split(envp[i], '=');
        if (key[0] != NULL)
            add_env(mshell,key[0], key[1]);
        free_array(key);
        i++;
    }
}

/*int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    //int i = 0;
    init_struct(&mshell, envp);
    ft_env(mshell.env);
    clear_mshell(&mshell);
    //while(mshell.envp[i])
        //printf("\n\n%s\n", mshell.envp[i++]);
    //printf("%d\n", mshell.env->n_env);
    return 0;
}*/