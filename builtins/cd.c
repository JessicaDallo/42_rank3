/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:19:07 by sheila            #+#    #+#             */
/*   Updated: 2024/12/05 17:41:05 by shrodrig         ###   ########.fr       */
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
    
	token = token->next;
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
    t_token *token1 = cr_token(CMD, "echo");
	t_token *token2 = cr_token(ARG, "ola");
    t_token *token3 = cr_token(ARG, "\"\'$USER\'\"");
    t_token *token4 = cr_token(ARG, " \"   bom   \"");
    t_token *token5 = cr_token(ARG, "dia      ?");
	t_token *token6 = cr_token(ARG, "\' \"$PWD\" \'");

    // Conecte os tokens
    token1->next = token2;
    token2->next = token3;
	token3->next = token4;
    token4->next = token5;
	token5->next = token6;

    return token1; // Retorna o início da lista
}*/

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
//     t_minishell mshell;
    
//     init_struct(&mshell, envp);
// 	t_token *tokens = cr_sample_tokens();
	
//    	if (argc > 2)
//    	{
//        ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
//        return (1);
//    }
//    if (argc == 2)
//        ft_cd(&mshell, argv[1]);
//    else
//        ft_cd(&mshell, NULL);
//    return (0);
// }