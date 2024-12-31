/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:34:25 by sheila            #+#    #+#             */
/*   Updated: 2024/12/23 15:36:23 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

bool is_expand(char *delim)
{
	if (ft_strchr(delim, '\''))
		return(false);
	else if (ft_strchr(delim, '\"'))
		return (false);
	else
	return(true);
}

char *get_epos(char *line, int flag)
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

void expand_exit(t_minishell *mshell, char **line, int flag)
{
	char 	*e_pos;
	char	*new_line;
	char	*temp;
	char	*exit;
		
	e_pos = get_epos(*line, flag);
	while (e_pos)
	{
		exit = ft_itoa(mshell->e_code);
		temp = ft_strjoin((ft_substr(*line, 0, e_pos - *line)), exit);
		new_line = ft_strjoin(temp, (e_pos + 2));
		free(temp);
		free(*line);
		*line = new_line;
		e_pos = get_epos(*line, flag);
	}
}