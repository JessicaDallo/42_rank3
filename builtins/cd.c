/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:19:07 by sheila            #+#    #+#             */
/*   Updated: 2024/10/30 18:34:23 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

char	*go_path(char *env)
{
    char    *path;
	path = getenv(env);
    if (!path)
    {
        if (ft_strcmp(env, "HOME") == 0)
            perror_msg("cd", "HOME is not set");
        else
            perror_msg("cd", "OLDPWD is not set");
        return(NULL);
    }
    return(path);
}

void    ft_cd(t_minishell *mshell, char *args)
{
    char    *oldpwd;
    char    pwd[PATH_MAX];
    char    *path;
    
    if(!(oldpwd = getcwd(pwd, sizeof(pwd))))
    {
        perror("getcwd() error:");
        return;
    }
    if (!args || (args[0] == '~'))
        path = expand_tilde(args);
    else if (args [0] == '-')
    {
        path = go_path("OLDPWD");
        ft_putstr_fd(path, STDOUT_FILENO);
    }
    //else if (args [0] == '.' && args[1] == '.')
    //    path = "..";
    //else if(args[0] == '.')
    //    return;
    else
        path = args;
    if(chdir(path) != 0)
        perror("cd");
    env_renew(mshell, "OLDPWD", oldpwd);
    getcwd(pwd, sizeof(pwd));
    env_renew(mshell, "PWD", pwd);
}

//int main(int argc, char **argv, char **envp)
//{
//    t_minishell mshell;

//    init_struct(&mshell, &mshell.env, envp);
    
//    if (argc > 2)
//    {
//        ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
//        return (1);
//    }
//    if (argc == 2)
//        ft_cd(&mshell, argv[1]);
//    else
//        ft_cd(&mshell, NULL);
//    return (0);
//}