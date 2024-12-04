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

void get_tokens(char **cmd)
{
	//fazer uma logica par afazer split de espacos cada cmd tem que ser feito
	//o split no temp
	t_token	*tokens
	char	**temp;
	int		i;
	int		j;

	tmp = ft_split(cmd[j], ' ');
	i = 0;
	j = 0;
	type = get_type(temp[i]);
	while(type[i])
	{
		add_token(&token, cmd[i], type);
		i++;
	}
}

void	handle_imput(char *input)
{
	//t_token *tokens;
	char **cmd;
	int i;

	token = NULL;

	cmd = ft_split(input, '|');
	ft_print_array(cmd);
	get_tokens(cmd);

}