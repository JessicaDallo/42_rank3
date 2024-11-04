/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:56:58 by shrodrig          #+#    #+#             */
/*   Updated: 2024/10/29 16:05:28 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void env_renew(t_minishell *mshell, char *key, char *value)
{
    int i;

    i = -1;
	while (mshell->env.keys[++i])
    {
        if (strncmp(mshell->env.keys[i], key, (ft_strlen(key)) == 0))
        {
			free(mshell->env.values[i]);
            if(value)
	            mshell->env.values[i] = ft_strdup(value);
            else
                mshell->env.values[i] = ft_strdup("");
            break;
		}
	}
}

void init_env(t_minishell *mshell)
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
}

void    ft_env(t_env env)
{
    int i;
    
    i = -1;
    while(env.keys[++i])
    {
        ft_putstr_fd(env.keys[i], STDOUT_FILENO);
        ft_putstr_fd("=", STDOUT_FILENO);
        ft_putstr_fd(env.values[i], STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
    return;
}

/*int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    int i = 0;
    init_struct(&mshell, &mshell.env, envp);
    
    while(mshell.envp[i])
        printf("%s\n", mshell.envp[i++]);
    return 0;
}*/