/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:12:37 by jesilva-          #+#    #+#             */
/*   Updated: 2024/12/23 10:12:41 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	split_delimiter(t_split *spl, char *str, char c)
{
	if (str[spl->i] == c && spl->i > spl->init)
	{
		spl->arr[spl->j++] = ft_strndup(&str[spl->init], spl->i - spl->init);
		spl->init = spl->i + 1;
	}
	if ((size_t)spl->i < ft_strlen(str))
		spl->i++;
	else
		return (0);
	return (1);
}

static void	spl_quotes(t_split *spl, char *str, char c)
{
	spl->i = spl->i + quote_count(&str[spl->i], str[spl->i]);
	if (str[spl->i] == c)
	{
		spl->arr[spl->j++] = ft_strndup(&str[spl->init], spl->i - spl->init);
		spl->init = spl->i + 1;
	}
}

static void	process_split(t_split *spl, char *str, char c)
{
	while (str[spl->i] != '\0')
	{
		if (str[spl->i] == '"' || str[spl->i] == '\'')
			spl_quotes(spl, str, c);
		else
		{
			if (!split_delimiter(spl, str, c))
				break ;
		}
	}
}

static void	process_split_red(t_split *spl, char *str, char c)
{
	while (str[spl->i] != '\0')
	{
		spl->redir = is_redir(spl, str);
		if (str[spl->i] == '"' || str[spl->i] == '\'')
			spl_quotes(spl, str, c);
		else if (spl->redir)
		{
			if (spl->i > spl->init)
				spl->arr[spl->j++] = ft_strndup(&str[spl->init], \
				spl->i - spl->init);
			spl->arr[spl->j++] = ft_strndup(&str[spl->i], spl->redir);
			spl->i += spl->redir;
			spl->init = spl->i;
		}
		else
			if (!split_delimiter(spl, str, c))
				break ;
	}
}

char	**ft_split_quots(char *str, char c)
{
	t_split	spl;

	spl.i = 0;
	spl.j = 0;
	spl.init = spl.i;
	spl.arr = NULL;
	spl.rlen = len_red(str, c);
	spl.cwords = ft_count_words(str, c);
	spl.total = spl.cwords + spl.rlen;
	spl.arr = ft_calloc(spl.total + 1, sizeof(char *));
	if (!spl.arr)
		return (NULL);
	if (c == ' ')
		process_split_red(&spl, str, c);
	else
		process_split(&spl, str, c);
	if (spl.init < spl.i)
		spl.arr[spl.j++] = ft_strndup(&str[spl.init], spl.i - spl.init);
	spl.arr[spl.j] = NULL;
	process_trim(&spl);
	return (spl.arr);
}
