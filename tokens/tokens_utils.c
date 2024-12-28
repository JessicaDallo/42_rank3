/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:09:52 by jesilva-          #+#    #+#             */
/*   Updated: 2024/12/23 19:09:55 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include_builtins.h"

bool	is_delimiter(char *arg)
{
	if (ft_strcmp(arg, "|") == 0 || ft_strcmp(arg, "<") == 0
		|| ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0
		|| ft_strcmp(arg, "<<") == 0 || !arg)
		return (true);
	return (false);
}

int	quote_count(char *str, char c)
{
	int	i;

	i = 0;
	i++;
	while (str[i] != c)
	{
		i++;
	}
	i++;
	return (i);
}

int	ft_count_words(char *s, char c)
{
	int		i;
	int		j;
	char	quots;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c)
			j++;
		if (s[j] && s[j] != c)
		{
			i++;
		}
		while (s[j]&& s[j] != c)
		{
			if (s[j] == '"' || s[j] == '\'')
			{
				quots = s[j];
				j++;
				while (s[j] && s[j] != quots)
					j++;
			}
			j++;
		}
	}
	return (i);
}

void	ft_print_array(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("%s ->array\n", cmd[i]);
		i++;
	}
}

void	ft_print_tokens(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_token	*bla;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->tokens)
		{
			printf("T_CMD input -> %s\n", tmp->tokens->input);
			bla = tmp->tokens;
			while (bla != NULL)
			{
				printf("T_TOKEN input -> %s\n", bla->input);
				printf("T_TOKEN type -> %i\n", bla->type);
				bla = bla->next;
			}
		}
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break ;
	}
}
