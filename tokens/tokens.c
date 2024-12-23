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

	while (*h_input)
	{
		add_cmd(&cmd);
		temp = ft_split_quots(*h_input, ' ');
		ft_print_array(temp);
		if (temp)
		{
			process_tokens(temp, &cmd);
			free_array(temp);
			temp = NULL;
		}
		h_input++;
	}
	ft_print_tokens(&cmd);
	return (cmd);
}

t_cmd	*parse_input(char *input)
{
	t_cmd	*cmd;
	char	**h_input;

	cmd = NULL;
	input = rm_space(input);
	printf("%s -> teste \n", input);
	h_input = ft_split_quots(input, '|');
	cmd = get_tokens(cmd, h_input);
	free_array(h_input);
	h_input = NULL;
	return (cmd);
}
