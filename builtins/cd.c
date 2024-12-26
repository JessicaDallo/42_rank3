/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:19:07 by sheila            #+#    #+#             */
/*   Updated: 2024/12/23 16:31:30 by sheila           ###   ########.fr       */
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
char    *check_tilde(char *input)
{
    char    *path_expand;
    
    if (!input || (input[0] == '~' && input[1] == '\0'))
        return(path_expand = go_path("HOME"));
    else if(input[0] == '~')
        return (path_expand = ft_strjoin(go_path("HOME"), input + 1));
    return(NULL);
}

void    ft_cd(t_minishell *mshell, t_token *token)
{
    char    *oldpwd;
    char    pwd[PATH_MAX];
    char    *path;
    
	token = token->next;
    if(!(oldpwd = getcwd(pwd, sizeof(pwd))))
    {
        perror("getcwd() error:");
        return;
    }
    if (!token->input || token->input[0] == '~')
        path = check_tilde(token->input);
    else if (token->input[0] == '-')
    {
        path = go_path("OLDPWD");
        ft_putstr_fd(path, STDOUT_FILENO);
    }
    else
        path = token->input;
    if(chdir(path) != 0)
        perror("cd");
    printf("PATH:%s\n", path);
    update_env(mshell, "OLDPWD",oldpwd, true);
    getcwd(pwd, sizeof(pwd));
    update_env(mshell, "PWD", pwd, true);
    free(path);
}
