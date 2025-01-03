/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:30 by sheila            #+#    #+#             */
/*   Updated: 2025/01/01 23:41:57 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	handle_expansions(t_minishell *mshell, char **line, int flag)
{
	if(!line || !*line) //se não tiver linha ou linha vazia EXPORT
		return;
	expand_exit(mshell, line, flag);
	expand_var(mshell, line, flag);
}

char	*get_position(char *line, int flag)
{
	char quote;

	while (*line)
	{
		if (flag && (*line == '\'' || *line == '\"'))
		{
			quote = *line++;
			while (*line && *line != quote)
			{
				if (quote == '\"' && *line == '$' && 
					(ft_isalnum(*(line + 1)) || *(line + 1) == '_'))
					return (line);
				line++;
			}
		}
		if (*line == '$' && (ft_isalnum(*(line + 1)) || *(line + 1) == '_'))
			return (line);
		line++;
	}
	return (NULL);
}

void	update_line(char **line, char *value, char *str)
{
	char *new_line;
	char *temp;

	if (!(*line)[0] && !value)
		temp = ft_strdup("");
	else if (!(*line)[0] && value)
		temp = ft_strdup(value);
	else if (!value)
		temp = ft_strdup(*line);
	else
		temp = ft_strjoin(*line, value);
	new_line = ft_strjoin(temp, str);
	free(temp);
	free(*line);
	*line = new_line;
}

void	expand_var(t_minishell *mshell, char **line, int flag)
{
	char *var_pos;
	char *key;
	char *value;
	int len;

	var_pos = get_position(*line, flag);
	while (var_pos)
	{
		len = 0;
		while (ft_isalnum(var_pos[len + 1]) || var_pos[len + 1] == '_')
			len++;
		key = ft_substr(var_pos, 1, len);
		*var_pos = '\0';
		value = get_value(mshell, key);
		update_line(line, value, var_pos + len + 1);
		free(key);
		var_pos = get_position(*line, flag);
	}
}
