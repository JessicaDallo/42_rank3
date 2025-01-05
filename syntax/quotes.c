/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:39:57 by sheila            #+#    #+#             */
/*   Updated: 2025/01/04 23:04:36 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	process_char(char current, char *prev, char *result, bool *insid_quote)
{
	static char	quote_char = '\0';

	if (current == '\'' || current == '\"')
	{
		if (*insid_quote && current == quote_char)
		{
			*insid_quote = false;
			quote_char = '\0';
		}
		else if (!*insid_quote)
		{
			*insid_quote = true;
			quote_char = current;
		}
		*result = current;
		return (true);
	}
	if (*insid_quote || (current != ' ' || (prev && *prev != ' ')))
	{
		*result = current;
		return (true);
	}
	return (false);
}

char	*rm_space(char *str)
{
	char	*result;
	char	prev;
	bool	inside_quotes;
	size_t	j;
	size_t	i;

	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	inside_quotes = false;
	while (str[i])
	{
		if (i > 0)
			prev = result[j - 1];
		else
			prev = '\0';
		if (process_char(str[i], &prev, &result[j], &inside_quotes))
			j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*handle_quotes(char *str, int s_quote, int d_quote)
{
	char	*output;
	char	*temp;
	char	*aux;
	size_t	i;

	output = ft_strdup("");
	temp = rm_space(str);
	i = -1;
	if (temp && temp[0] == '$' && (temp[1] == '\'' || temp[1] == '\"'))
		i++;
	while (++i < (ft_strlen(temp)))
	{
		if (temp[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (temp[i] == '"' && !s_quote)
			d_quote = !d_quote;
		else
		{
			aux = ft_appendchar(output, temp[i]);
			free(output);
			output = aux;
		}
	}
	free(temp);
	return (output);
}
