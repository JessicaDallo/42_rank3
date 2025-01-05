/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:56:16 by jesilva-          #+#    #+#             */
/*   Updated: 2025/01/04 23:24:42 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process_tokens(char **temp, t_cmd **cmd)
{
	token_type	type;
	bool		new_cmd;
	int			i;

	i = 0;
	new_cmd = true;
	while (temp[i])
	{
		type = get_type(temp[i], new_cmd);
		if (type == 0 && temp[i][1] != '$')
		{
			if (ft_strncmp(temp[i], "\"\"", 3) != 0
				&& ft_strncmp(temp[i], "\'\'", 3) != 0)
				temp[i] = handle_quotes(temp[i], 0, 0);
		}
		if (is_delimiter(temp[i]))
			i++;
		add_token(cmd, temp[i], type, new_cmd);
		new_cmd = false;
		i++;
	}
}

t_cmd	*get_tokens(t_cmd *cmd, char **h_input)
{
	char		**temp;
	char		**cpy_input;

	cpy_input = h_input;
	while (*cpy_input) //linha 43
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
