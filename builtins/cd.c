/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:19:07 by sheila            #+#    #+#             */
/*   Updated: 2025/01/09 01:19:37 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*go_path(t_minishell *mshell, char *env)
{
	char		*path;

	path = ft_strdup(get_value(mshell, env));
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
	char	*path_expand;
	char	*clean;

	g_e_code = 0;
	if (!input || (input[0] == '~' && input[1] == '\0'))
		return (path_expand = go_path(mshell, "HOME"));
	else if (input[0] == '~')
		return (path_expand = ft_strjoin(go_path(mshell, "HOME"), input + 1));
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

void	get_path(t_minishell *mshell, t_token *token, char **path)
{
	g_e_code = 0;
	if (token->next)
	{
		error_msg("cd", "too many arguments", 1);
		return ;
	}
	else if (token->input[0] == '~')
	{
		if (token->input[1] == '\0')
			*path = go_path(mshell, "HOME");
		else
			*path = ft_strjoin(go_path(mshell, "HOME"), token->input + 1);
	}
	else if (token->input[0] == '-' && token->input[1] == '\0')
	{
		*path = go_path(mshell, "OLDPWD");
		if (*path)
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

	oldpwd = get_value(mshell, "PWD");
	path = NULL;
	if (!token->next || !token->next->input)
		path = go_path(mshell, "HOME");
	else
		get_path(mshell, token->next, &path);
	if (g_e_code == 1 || !path || !*path)
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
