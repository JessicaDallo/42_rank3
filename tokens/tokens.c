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

void get_tokens(char **h_input)
{
	token_type type;
	t_cmd	*cmd;
	char	**temp;
	int		i;
	bool	teste;

	cmd = NULL;
	while(*h_input)
	{
		add_cmd(&cmd);
		teste = true;
		i = 0;
		temp = ft_split(*h_input, ' ');
		while(temp[i])
		{
			type = get_type(temp[i], teste);
			if(is_delimiter(temp[i]))
				i++;
			add_token(&cmd, temp[i], type, teste);
			teste = false;
			i++;
		}
		free_array(temp);
		h_input++;
	}
	//REMOVER É APENAS PARA TESTAR 
	ft_print_tokens(&cmd);
}
void	parse_input(char *input)
{

	char **h_input;

	h_input = ft_split(input, '|');
	ft_print_array(h_input);
	get_tokens(h_input);

}