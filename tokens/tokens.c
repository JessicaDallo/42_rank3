/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:56:16 by jesilva-          #+#    #+#             */
/*   Updated: 2024/12/04 14:56:18 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include_builtins.h"

void	process_split(t_split *spl, char *str, char c)
{
	char	*temp;

	while (str[spl->i] != '\0')
	{
		if (str[spl->i] == '"' || str[spl->i] == '\'')
		{
			spl->i = spl->i + quote_count(&str[spl->i], str[spl->i]);
			if (str[spl->i] == c)
			{
				temp = ft_strndup(&str[spl->init], spl->i - spl->init);
				spl->arr[spl->j++] = temp;
				spl->init = spl->i + 1;
			}
		}
		else if (str[spl->i] == c && spl->i > spl->init)
		{
			temp = ft_strndup(&str[spl->init], spl->i - spl->init);
			spl->arr[spl->j++] = temp;
			spl->init = spl->i + 1;
		}
		if((size_t)spl->i < ft_strlen(str))
			spl->i++;
		else
			break ;
	}
}

char	**ft_split_quots(char *str, char c)
{
	t_split	spl;
	char	**arr;

	spl.i = 0;
	spl.j = 0;
	spl.init = spl.i;
	spl.arr = NULL;
	arr = ft_calloc(sizeof(char *), ft_count_words(str, c) + 1);
	if (!arr)
		return (NULL);
	spl.arr = arr;
	process_split(&spl, str, c);
	if (spl.init < spl.i)
		spl.arr[spl.j++] = ft_strndup(&str[spl.init], spl.i - spl.init);
	spl.arr[spl.j] = NULL;
	return (spl.arr);
}

void	get_tokens(char **h_input)
{
	token_type	type;
	t_cmd		*cmd;
	char		**temp;
	int			i;
	bool		new_cmd;

	cmd = NULL;
	while (*h_input)
	{
		add_cmd(&cmd);
		new_cmd = true;
		i = 0;
		temp = ft_split_quots(*h_input, ' ');
		while (temp[i])
		{
			type = get_type(temp[i], new_cmd);
			if (is_delimiter(temp[i]))
				i++;
			add_token(&cmd, temp[i], type, new_cmd);
			new_cmd = false;
			i++;
		}
		h_input++;
		free_array(temp);
		temp = NULL;
	}
	free_array(temp);
	free_cmd(cmd);
}

void	parse_input(char *input)
{
	char	**h_input;

	h_input = ft_split_quots(input, '|');
	get_tokens(h_input);
	free_array(h_input);
	h_input = NULL;
}
