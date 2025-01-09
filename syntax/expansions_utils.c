/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:34:25 by sheila            #+#    #+#             */
/*   Updated: 2025/01/09 02:25:30 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_expand(char *delim)
{
	if (ft_strchr(delim, '\''))
		return (false);
	else if (ft_strchr(delim, '\"'))
		return (false);
	else
		return (true);
}

char	*get_epos(char *line, int flag)
{
	char	quote;

	while (*line)
	{
		if (flag && (*line == '\'' || *line == '\"'))
		{
			quote = *line++;
			while (*line && *line != quote)
			{
				if (quote == '\"' && *line == '$' && *(line + 1) == '?')
					return (line);
				line++;
			}
		}
		if (*line == '$' && *(line + 1) == '?')
			return (line);
		line++;
	}
	return (NULL);
}

void	expand_exit(char **line, int flag)
{
	char	*e_pos;
	char	*new_line;
	char	*temp;
	char	*exit;
	char	*substr;

	e_pos = get_epos(*line, flag);
	while (e_pos)
	{
		exit = ft_itoa(g_e_code);
		substr = ft_substr(*line, 0, e_pos - *line);
		temp = ft_strjoin(substr, exit);
		new_line = ft_strjoin(temp, (e_pos + 2));
		free(temp);
		free(*line);
		free(exit);
		free(substr);
		*line = new_line;
		e_pos = get_epos(*line, flag);
	}
}

void	handle_expansion_hd(t_minishell *mshell, char *line, bool expand)
{
	if (expand)
		handle_expansions(mshell, &line, 1);
	ft_putendl_fd(line, mshell->heredoc_fd);
	free(line);
}

void	close_heredoc(t_minishell *mshell, char *eof)
{
	close(mshell->heredoc_fd);
	free(eof);
	close_pipes(mshell->commands);
	clear_mshell(mshell);
}
