/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:19:07 by sheila            #+#    #+#             */
/*   Updated: 2024/12/04 18:05:40 by shrodrig         ###   ########.fr       */
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

void    ft_cd(t_minishell *mshell, t_token *token)
{
    char    *oldpwd;
    char    pwd[PATH_MAX];
    char    *path;
    
    if(!(oldpwd = getcwd(pwd, sizeof(pwd))))
    {
        perror("getcwd() error:");
        return;
    }
    if (!token->input || (token->input[0] == '~'))
        path = go_path("HOME");
    else if (token->input[0] == '-')
    {
        path = go_path("OLDPWD");
        ft_putstr_fd(path, STDOUT_FILENO);
    }
    else
        path = token->input;
    if(chdir(path) != 0)
        perror("cd");
    update_env(mshell, "OLDPWD",oldpwd);
    getcwd(pwd, sizeof(pwd));
    update_env(mshell, "PWD", pwd);
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