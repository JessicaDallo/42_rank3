/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:56:16 by jesilva-          #+#    #+#             */
/*   Updated: 2025/01/07 20:07:24 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_t(t_cmd **cmd, char **arr, int *i, bool *new_cmd)
{
	t_token_type		type;
	char				*tmp;

	tmp = NULL;
	type = get_type(arr[*i], *new_cmd);
	//if (type == 0 && arr[*i][1] != '$')
	//{
	//	if (ft_strncmp(arr[*i], "\"\"", 3) != 0
	//		&& ft_strncmp(arr[*i], "\'\'", 3) != 0)
	//		tmp = handle_quotes(arr[*i], 0, 0);
	//}
	if (tmp)
	{
		add_token(cmd, tmp, type, *new_cmd);
		free(tmp);
		tmp = NULL;
	}
	else
	{
		if (is_delimiter(arr[*i]))
			(*i)++;
		add_token(cmd, arr[*i], type, *new_cmd);
	}
}

static void	process_tokens(char **temp_arr, t_cmd **cmd)
{
	bool			new_cmd;
	int				i;

	i = 0;
	new_cmd = true;
	while (temp_arr[i])
	{
		process_t(cmd, temp_arr, &i, &new_cmd);
		new_cmd = false;
		i++;
	}
}

t_cmd	*get_tokens(t_cmd *cmd, char **h_input)
{
	char		**temp;
	char		**cpy_input;

	cpy_input = h_input;
	while (*cpy_input)
	{
		add_cmd(&cmd);
		temp = ft_split_quots(*cpy_input, ' ');
		if (temp)
		{
			process_tokens(temp, &cmd);
			free_array(temp);
			temp = NULL;
		}
		cpy_input++;
	}
	return (cmd);
}

t_cmd	*parse_input(char *input)
{
	t_cmd	*cmd;
	char	**h_input;
	char	*trimmed;

	cmd = NULL;
	input = rm_space(input);
	if (!input)
		return (NULL);
	trimmed = ft_trim(input);
	free(input);
	if (!trimmed)
		return (NULL);
	h_input = ft_split_quots(trimmed, '|');
	free(trimmed);
	if (!h_input)
		return (NULL);
	cmd = get_tokens(cmd, h_input);
	free_array(h_input);
	h_input = NULL;
	return (cmd);
}
