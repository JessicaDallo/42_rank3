/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:30 by sheila            #+#    #+#             */
/*   Updated: 2024/11/07 19:33:28 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	handle_expansions(t_minishell *mshell, char **line)
{
	exit_expand(mshell, line);
	vars_expand(mshell, line);
}

char	*get_position(char *line)
{
	while(*line)
	{
		if (*line == '\'')
		{
			line++;
			while(*line && *line != '\'')
				line++;
		}
		if(*line == '\"')
		{
			line++;
			while(*line && *line != '\"')
			{
				if(*line == '$' && (ft_isalnum(*line) || line == '_'))
					return(line);
				line++;
			}
		}
		if (line == '$' && (ft_isalnum(*line) || line == '_'))
			line++;
		return(line);
	}
	return (NULL);
}

void	update_line(char **line, char *value, char *str)
{
	char	*new_line;
	char	*temp;

	if(!*line && !value)
		temp = ft_strdup("");
	else if(!*line && value)
		temp = ft_strdup(value);
	else if (!value)
		temp = ft_strdup(*line);
	else
		temp = ft_strjoin(*line, value);
	new_line = ft_strjoin(temp, value);
	free(temp);
	free(*line);
	*line = new_line;
}

void	vars_expand(t_minishell *mshell, char **line)
{
	char	*key;
	char	*value;
	char	*var_pos;
	size_t	len;

	var_pos = get_position(*line);
	if(var_pos)
	{
		len = 0;
		while((ft_isalnum(*var_pos) || *var_pos == '_'))
		{
			len++;
			var_pos++;
		}
		*var_pos = '\0';
		key = ft_substr(var_pos, 1, len);
		value = get_value(mshell, key);
		update_line(line, value, (var_pos + 1 + len));
		free(key);
		vars_expand(mshell, line);
	}
}
