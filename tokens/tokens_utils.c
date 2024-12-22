/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:49:43 by jesilva-          #+#    #+#             */
/*   Updated: 2024/12/20 21:56:27 by sheila           ###   ########.fr       */
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
	char	quots;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			i++;
		}
		while (*s && *s != c)
		{
			if (*s == '"' || *s == '\'')
			{
				quots = *s;
				s++;
				while (*s && *s != quots)
					s++;
			}
			s++;
		}
	}
	return (i);
}

char	*ft_trim(char *str)
{
	int	j;
	int	i;
	int x;
	char *temp;

	i = 0;
	x = 0;
	j = ft_strlen(str) - 1;
	while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while(str[j] == ' ' || (str[j] >= 9 && str[j] <= 13))
		j--;
	temp = ft_calloc(sizeof(char), j - i);
	while(i <= j)
	{
		temp[x] = str[i];
		i++;
		x++;
	}
	temp[x] = '\0';
	return (temp);
}

void	process_trim(t_split *spl)
{
	int	i;

	i = 0;
	while(spl->arr[i] != NULL)
	{
		spl->arr[i] = ft_trim(spl->arr[i]);
		i++;
	}
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
