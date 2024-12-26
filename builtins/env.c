/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:56:58 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/23 17:18:29 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void    ft_env(t_env *env)
{
    t_env   *temp;
    
    temp = env;
    while(temp != NULL)
    {
        if(temp->print)
        {
            ft_putstr_fd(temp->key, STDOUT_FILENO);
            ft_putstr_fd("=", STDOUT_FILENO);
            ft_putstr_fd(temp->value, STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
        temp = temp->next;
    }
    return;
}

void    add_env(t_minishell *mshell, char *key, char *value, bool flag)
{
    t_env   *temp;
    t_env   *new_node;

    new_node = (t_env *)malloc(sizeof(t_env));
    if(!new_node)
        return;
    new_node->key = ft_strdup(key);
	if (value != NULL)
        new_node->value = ft_strdup(value);
    else
        new_node->value = ft_strdup("");
    new_node->print = flag;
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
void    init_env(t_minishell *mshell)
{
    char    **key;
    char    *value;
    int     i;
    
    i = 0;
    mshell->env = NULL;
    while(mshell->envp[i])
    {
        key = ft_split(mshell->envp[i], '=');
        value = ft_strdup(ft_strchr(mshell->envp[i], '=') + 1);
        if (key[0] != NULL)
            add_env(mshell,key[0], value, true);
        if(value)
            free(value);
        free_array(key);
        i++;
    }
}

void    init_struct(t_minishell *mshell, char **envp)
{
    int i;
    
    ft_bzero(mshell, sizeof(t_minishell));
    if(!mshell)
        return;
    i = 0;
    while(envp[i])
        i++;
    mshell->envp = (char **)malloc(sizeof(char *) * (i + 1));
    if(!mshell->envp)
        return;
    i = 0;
    while(envp[i])
    {
        mshell->envp[i] = ft_strdup(envp[i]);
        i++;
    }
    mshell->envp[i] = NULL;
    init_env(mshell);
}

/*int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    init_struct(&mshell, envp);
    ft_env(mshell.env);
    // int i = 0;
    // printf("\n ----- ENVP LIST -----\n");
    // while(mshell.envp[i])
    //     printf("\n%s\n", mshell.envp[i++]);
    //printf("%d\n", mshell.env->n_env);
    clear_mshell(&mshell);
    return 0;
}*/