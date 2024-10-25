/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:56:31 by shrodrig          #+#    #+#             */
/*   Updated: 2024/10/22 13:57:52 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

/*void init_env(t_minishell *mshell)
{
    int i;
    char **key;

    mshell->env.keys = (char **)malloc(sizeof(char *) * (mshell->env.n_env + 1));
    mshell->env.values = (char **)malloc(sizeof(char *) * (mshell->env.n_env + 1));
    if (!mshell->env.keys || !mshell->env.values)
        return;

    i = 0;
    while (mshell->envp[i])
    {
        key = ft_split(mshell->envp[i], '=');
        if (key[0] != NULL)
            //key = ft_strjoin("=", key[1]);  // Adicionar o '=' de volta
            mshell->env.keys[i] = ft_strdup(key[0]);
		if (key[1] != NULL)
            mshell->env.values[i] = ft_strdup(key[1]);
        //printf("Key: %s, Value: %s\n", mshell->env.keys[i], mshell->env.values[i]);
        free(key[0]);
        free(key[1]);
        free(key);
        i++;
    }
    mshell->env.keys[i] = NULL;
    mshell->env.values[i] = NULL; 
}

void    init_struct(t_minishell *mshell, t_env *env, char **envp)
{
    static int i;
    
    ft_bzero(mshell, sizeof(t_minishell));
    ft_bzero(env, sizeof(t_env));
    while(envp[i])
        i++;
    mshell->envp = (char **)malloc(sizeof(char *) * (i +1));
    if(!mshell->envp)
        return;
    mshell->env.n_env = i;
    i = 0;
    while(envp[i])
    {
        mshell->envp[i] = ft_strdup(envp[i]);
        i++;
    }
    mshell->envp[i] = NULL;
    init_env(mshell);
}*/

void ft_unset(t_minishell *mshell, char *var)
{
    int i = 0;
    size_t len = ft_strlen(var);
    
    if (!*var)
        return;
    while (mshell->env.keys[i])
    {
        if (strncmp(mshell->env.keys[i], var, len) == 0)
        {
            free(mshell->env.keys[i]);
            free(mshell->env.values[i]);
            while (mshell->env.keys[i + 1])
            {
                mshell->env.keys[i] = mshell->env.keys[i + 1];
                mshell->env.values[i] = mshell->env.values[i + 1];
                i ++;
            }
            mshell->env.keys[i] = NULL;   
            mshell->env.values[i] = NULL;
            mshell->env.n_env--;
            break;
        }
        i++;
    }
}

/*int main(int argc, char **argv, char **envp)
{
    t_minishell mshell;
    //t_env env;

    init_struct(&mshell, &mshell.env, envp);
    
    printf("\n--- Antes do unset ---\n");
        int i = -1;
    while (mshell.env.keys[++i])
        printf("%s = %s\n", mshell.env.keys[i], mshell.env.values[i]);
    if (argc > 1)
        ft_unset(&mshell, argv[1]);
    
    printf("\n--- Após o unset ---\n");
    i = -1;
    while (mshell.env.keys[++i])
        printf("%s = %s\n", mshell.env.keys[i], mshell.env.values[i]);

    return 0;
}*/