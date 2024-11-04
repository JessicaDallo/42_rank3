/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:16:30 by sheila            #+#    #+#             */
/*   Updated: 2024/10/28 13:30:23 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void    get_value(t_minishell *mshell, char *value, int n)
{
    if(value)
	    mshell->env.values[n] = ft_strdup(value);
    else
        mshell->env.values[n] = ft_strdup("");
}

void    get_newkey(t_minishell *mshell, char **temp)
{
    int i;
    int flag;

    i = -1;
    flag = 0;
	while (mshell->env.keys[++i])
    {
        if (strncmp(mshell->env.keys[i], temp[0], (ft_strlen(temp[0])+1)) == 0)
        {
			free(mshell->env.values[i]);
			flag = 1;
            get_value(mshell, temp[1], i);
            break;
		}
	}
    if(!flag)
	{
		mshell->env.keys[mshell->env.n_env] = ft_strdup(temp[0]);
        get_value(mshell, temp[1], mshell->env.n_env);
		mshell->env.n_env++;
	}
}

void ft_export(t_minishell *mshell, char **vars)
{
	char	**temp;

    while(*vars)
    {
        if (!*vars)
            return;
        temp = ft_split(*vars, '=');
	    if(!temp)
		    return;
        get_newkey(mshell, temp);
        free(temp[0]);
        free(temp[1]);
        free(temp);
        vars++;
    }
    mshell->env.keys[mshell->env.n_env] = NULL;
    mshell->env.values[mshell->env.n_env] = NULL;
}

/*int main(int argc, char **argv, char **envp)
{
    t_minishell mshell;
    t_env env;

    init_struct(&mshell, &env, envp);
    
    printf("\n--- Antes do export ---\n");
        int i = -1;
    while (mshell.env.keys[++i])
        printf("%s = %s\n", mshell.env.keys[i], mshell.env.values[i]);
    if (argc > 1)
        ft_export(&mshell, ++argv);
    
    printf("\n--- Após o export ---\n");
    i = -1;
    while (mshell.env.keys[++i])
        printf("%s=%s\n", mshell.env.keys[i], mshell.env.values[i]);

    return 0;
}*/