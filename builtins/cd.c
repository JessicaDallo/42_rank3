/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:19:07 by sheila            #+#    #+#             */
/*   Updated: 2025/01/01 23:00:23 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

char	*go_path(char *env)
{
	t_minishell	**mshell;
	char		*path;

	mshell = get_shell();
	path = get_value(*mshell, env);
	if (!path)
	{
		if (ft_strcmp(env, "HOME") == 0)
			error_msg("cd", "HOME is not set", 1);
		else
			error_msg("cd", "OLDPWD is not set", 1);
		return(NULL);
	}
	return(path);
}

char	*check_tilde(char *input)
{
	t_minishell	**mshell;
	char		*path_expand;

	mshell = get_shell();
	(*mshell)->e_code = 0;
	if (!input || (input[0] == '~' && input[1] == '\0'))
		return(path_expand = go_path("HOME"));
	else if(input[0] == '~')
		return (path_expand = ft_strjoin(go_path("HOME"), input + 1));
	else if(input[0] == '$')
	{
		handle_expansions(*mshell, &input, 1);
		return(input);
	}
	return(NULL);
}

void	get_path(t_minishell *mshell, t_token *token, char **path, bool *flag)
{
	*flag = false;
	if(token->next)
	{
		error_msg("cd", "too many arguments", 1);
		return;
	}
	else if(token->input[0] == '~')
	{
		if(token->input[1] == '\0')
			*path = go_path("HOME");
		else
		{
			*flag = true;
			*path = ft_strjoin(go_path("HOME"), token->input + 1);
		}
	}
	else if (token->input[0] == '-' && token->input[1] == '\0')
	{
		*path = go_path("OLDPWD");
		if(*path)
			ft_putendl_fd(*path, STDOUT_FILENO);
	}
	else
		*path = handle_quotes(token->input, 0, 0);
	handle_expansions(mshell, path, 1);
}

void	ft_cd(t_minishell *mshell, t_token *token)
{
	char	*oldpwd;
	char	*newpwd;
	char	*path;
	bool	flag;
	
	path = NULL;
	oldpwd = get_value(mshell, "PWD");
	if (!token->next || !token->next->input)
		path = go_path("HOME");
	else
		get_path(mshell, token->next, &path, &flag);
	if(!path || path[0] == '\0')
		return;
	if(chdir(path) != 0)
		error_msg("cd", "No such file or directory", 1);
	update_env(mshell, "OLDPWD",oldpwd, true);
	newpwd = getcwd(NULL, 0);
	if(!newpwd)
		newpwd = ft_strdup(path);
	update_env(mshell, "PWD", newpwd, true);
	if(flag)
		free(path);
	if(newpwd)
		free(newpwd);
}

