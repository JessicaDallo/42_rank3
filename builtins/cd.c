/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:19:07 by sheila            #+#    #+#             */
/*   Updated: 2024/12/05 19:57:10 by sheila           ###   ########.fr       */
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
char    *check_tilde(char    *input)
{
    char    *path_expand;
    
    if (!input || (input[0] == '~' && input[1] == '\0'))
        path_expand = go_path("HOME");
    else if(input[0] == '~')
        path_expand = ft_strjoin(go_path("HOME"), input + 1);
    return(path_expand);
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
    //printf("PATH:%s\n", path);
    update_env(mshell, "OLDPWD",oldpwd);
    getcwd(pwd, sizeof(pwd));
    update_env(mshell, "PWD", pwd);
}

/*t_token *cr_token(token_type type, const char *input)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->input = strdup(input); // Copia o valor da string
    new_token->next = NULL;
    return new_token;
}

t_token *cr_sample_tokens()
{
    t_token *token1 = cr_token(CMD, "CD");
	t_token *token2 = cr_token(ARG, "~/Desktop");
    //t_token *token3 = cr_token(ARG, "lalala");


    // Conecte os tokens
    token1->next = token2;
    //token2->next = token3;

    return token1; // Retorna o início da lista
}

 int main(int argc, char **argv, char **envp)
 {
     (void)argc;
     (void)argv;
     t_minishell mshell;
    
    init_struct(&mshell, envp);
 	t_token *tokens = cr_sample_tokens();
	
    if (tokens)
        ft_cd(&mshell,tokens);
    return (0);
 }*/