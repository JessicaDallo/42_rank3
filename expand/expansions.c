/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:30 by sheila            #+#    #+#             */
/*   Updated: 2024/11/07 23:02:14 by sheila           ###   ########.fr       */
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

void	expand_variables(t_minishell *mshell, char **line)
{
	char	*var_pos;
	char	*key;
	char	*value;
	int		len;

	var_pos = find_var_position(**line);
	while (var_pos)
	{
		if (var_pos > *line && *(var_pos - 1) == '\\')
		{
			ft_memmove(var_pos - 1, var_pos, ft_strlen(var_pos) + 1);
			var_pos = find_var_position(var_pos);
			continue;
		}
		len = 0;
		while (is_varname(var_pos[len + 1]))
			len++;
		key = ft_substr(var_pos, 1, len);
		*var_pos = '\0';
		value = get_value(mshell, key);
		update_input(line, value, var_pos + 1 + len);
		free(key);
		var_pos = find_var_position(*line);
	}
}
