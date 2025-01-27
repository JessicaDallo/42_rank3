/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:19:07 by sheila            #+#    #+#             */
/*   Updated: 2025/01/12 15:16:36 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*go_path(t_minishell *mshell, char *env)
{
	char	*path;
	char	*value;

	value = get_value(mshell, env);
	if (value)
		path = ft_strdup(value);
	else
		path = NULL;
	if (!path)
	{
		if (ft_strcmp(env, "HOME") == 0)
			error_msg("cd", "HOME is not set", 1);
		else
			error_msg("cd", "OLDPWD is not set", 1);
		return (NULL);
	}
	return (path);
}

char	*check_tilde(t_minishell *mshell, char *input)
{
	char	*clean;

	if (!input || (input[0] == '~' && input[1] == '\0'))
		return (go_path(mshell, "HOME"));
	clean = handle_quotes(input, 0, 0);
	if (input[0] == '$' || ((input[0] == '\"' && input[1] == '$')))
	{
		handle_expansions(mshell, &clean, 1);
		if (!*clean)
		{
			free(clean);
			return (ft_strdup(input));
		}
	}
	return (clean);
}

char	*path_clean(t_minishell *mshell, char *input)
{
	char	*path_clean;

	if (ft_strncmp(input, "\"\"", 3) == 0)
		return (ft_strdup("."));
	path_clean = handle_quotes(input, 0, 0);
	if (input[0] == '$' || ((input[0] == '\"' && input[1] == '$')))
	{
		handle_expansions(mshell, &path_clean, 1);
		if (!*path_clean)
		{
			free(path_clean);
			return (go_path(mshell, "HOME"));
		}
	}
	return (path_clean);
}

void	get_path(t_minishell *mshell, t_token *token, char **path)
{
	char	*temp;

	if (token->next)
	{
		error_msg("cd", "too many arguments", 1);
		return ;
	}
	else if (token->input[0] == '~')
	{
		temp = go_path(mshell, "HOME");
		if (token->input[1] != '\0' && temp)
		{
			*path = ft_strjoin(temp, token->input + 1);
			free(temp);
		}
		else
			*path = temp;
	}
	else if (token->input[0] == '-' && token->input[1] == '\0')
		cd_minus(mshell, path);
	else
		*path = path_clean(mshell, token->input);
}

void	ft_cd(t_minishell *mshell, t_token *token)
{
	char	*oldpwd;
	char	*newpwd;
	char	*path;

	oldpwd = get_value(mshell, "PWD");
	path = NULL;
	g_e_code = 0;
	if (!token->next || !token->next->input)
		path = go_path(mshell, "HOME");
	else
		get_path(mshell, token->next, &path);
	if (g_e_code == 1 || !path)
	{
		free(path);
		return ;
	}
	if (chdir(path) != 0)
		error_msg("cd", "No such file or directory", 1);
	update_env(mshell, "OLDPWD", oldpwd, true);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		newpwd = ft_strdup(path);
	update_env(mshell, "PWD", newpwd, true);
	free(path);
	free(newpwd);
}
