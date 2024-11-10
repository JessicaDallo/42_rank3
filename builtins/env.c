/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:56:58 by shrodrig          #+#    #+#             */
/*   Updated: 2024/11/09 18:09:59 by sheila           ###   ########.fr       */
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

void init_env(t_minishell *mshell)
{
    int i = 0;
    char **key;

    i = 0;
    mshell->env = NULL;
    while (mshell->envp[i])
    {
        key = ft_split(mshell->envp[i], '=');
        if (key[0] != NULL)
            add_env(mshell,key[0], key[1]);
        free(key[0]);
        free(key[1]);
        free(key);
        i++;
    }
}

void    init_struct(t_minishell *mshell, char **envp)
{
    static int i;
    
    i = 0;
    ft_bzero(mshell, sizeof(t_minishell));
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
    
    //int i = 0;
    init_struct(&mshell, envp);
    ft_env(mshell.env);
    //while(mshell.envp[i])
        //printf("\n\n%s\n", mshell.envp[i++]);
    //printf("%d\n", mshell.env->n_env);
    return 0;
}*/

//void ft_env(t_env env);

//int main(int argc, char **argv, char **envp)
//{
//    t_minishell mshell;
	
//	(void)argv;
//	(void)argc;
//   init_struct(&mshell, &mshell.env, envp);
//   if (argc >1)
//		ft_env(mshell.env);
//   return 0;
//}