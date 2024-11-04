/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:56:31 by shrodrig          #+#    #+#             */
/*   Updated: 2024/10/28 18:30:01 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void ft_unset(t_minishell *mshell, char **vars)
{
    int i;
    size_t len;
    
    if (!*vars)
        return;
    while(*vars)
    {
        len = ft_strlen(*vars);
        i = 0;
        while (mshell->env.keys[i])
        {
            if (strncmp(mshell->env.keys[i], *vars, len) == 0)
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
        vars++;
    }
}

//int main(int argc, char **argv, char **envp)
//{
//    t_minishell mshell;
//    //t_env env;

//    init_struct(&mshell, &mshell.env, envp);
    
//    printf("\n--- Antes do unset ---\n");
//        int i = -1;
//    while (mshell.env.keys[++i])
//        printf("%s = %s\n", mshell.env.keys[i], mshell.env.values[i]);
//    if (argc > 1)
//        ft_unset(&mshell, argv);
    
//    printf("\n--- Após o unset ---\n");
//    i = -1;
//    while (mshell.env.keys[++i])
//        printf("%s = %s\n", mshell.env.keys[i], mshell.env.values[i]);

//    return 0;
//}