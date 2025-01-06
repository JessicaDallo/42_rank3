/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:56:16 by sheila            #+#    #+#             */
/*   Updated: 2025/01/05 19:34:04 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_redir_input(char *file)
{
	if (access(file, F_OK) == 0 && access(file, R_OK) < 0)
	{
		error_msg(file, "Permission denied", 1);
		return (false);
	}
	if (file[0] == '$')
	{
		error_msg(file, "ambiguous redirect", 1);
		return (false);
	}
	return (true);
}

bool	check_redir_out(char *file)
{
	if (access(file, F_OK) == 0 && access(file, W_OK) < 0)
	{
		error_msg(file, "Permission denied", 1);
		return (false);
	}
	if (file[0] == '$')
	{
		error_msg(file, "ambiguous redirect", 1);
		return (false);
	}
	return (true);
}

bool	redir_input(t_minishell *mshell, char *filename)
{
	int		fd;
	char	*file;

	file = check_tilde(mshell, handle_quotes(filename, 0, 0));
	if (!file || !*file)
		file = handle_quotes(filename, 0, 0);
	if (!check_redir_input(file))
		return (false);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		error_msg(file, "No such file or directory", 1);
		return (false);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		error_msg("dup2", "Error redirecting", 1);
		close(fd);
		return (false);
	}
	close(fd);
	free(file);
	return (true);
}

bool	redir_output(t_minishell *mshell, char *filename)
{
	int		fd;
	char	*file;

	file = check_tilde(mshell, handle_quotes(filename, 0, 0));
	if (!file)
		file = handle_quotes(filename, 0, 0);
	if (!check_redir_out(file))
		return (false);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		error_msg(file, "No such file or directory", 1);
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror_msg("dup2", "Error redirecting");
		close(fd);
		return (false);
	}
	close(fd);
	free(file);
	return (true);
}

bool	redir_append(t_minishell *mshell, char *filename)
{
	int		fd;
	char	*file;

	file = check_tilde(mshell, handle_quotes(filename, 0, 0));
	if (!file)
		file = handle_quotes(filename, 0, 0);
	if (!check_redir_out(file))
		return (false);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		error_msg(file, "No such file or directory", 1);
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror_msg("dup2", "Error redirecting");
		close(fd);
		return (false);
	}
	close(fd);
	free(file);
	return (true);
}
