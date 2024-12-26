/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_str_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:12:18 by jesilva-          #+#    #+#             */
/*   Updated: 2024/12/23 10:12:20 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include_builtins.h"

int	is_redir(t_split *spl, char *str)
{
	if (str[spl->i] == '<' || str[spl->i] == '>')
	{
		if (str[spl->i] == '<' && str[spl->i + 1] == '<')
			return (2);
		if (str[spl->i] == '>' && str[spl->i + 1] == '>')
			return (2);
		return (1);
	}
	return (0);
}

static int	count_red(char *str, int *i, int count)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		count = count + 2;
		*i = *i + 2;
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		count = count + 2;
		*i = *i + 2;
	}
	else
	{
		count = count + 1;
		(*i)++;
	}
	return (count);
}

int	len_red(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (c == '|')
		return (0);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			count = count + count_red(str, &i, count);
		}
		i++;
	}
	return (count);
}

char	*ft_trim(char *str)
{
	char	*temp;
	int		j;
	int		i;
	int		x;

	i = 0;
	x = 0;
	j = ft_strlen(str) - 1;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && i <= j)
		i++;
	if (str[i] == '\0')
		return (NULL);
	while ((str[j] == ' ' || (str[j] >= 9 && str[j] <= 13)) && i <= j)
		j--;
	temp = ft_calloc(sizeof(char), j - i);
	while (i <= j)
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
	char	*temp;
	int		i;

	i = 0;
	while (spl->arr[i] != NULL)
	{
		temp = ft_trim(spl->arr[i]);
		spl->arr[i] = temp;
		i++;
	}
}
