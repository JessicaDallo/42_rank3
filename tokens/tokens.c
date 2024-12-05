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
	//fazer uma logica par afazer split de espacos cada cmd tem que ser feito
	//o split no temp
	t_cmd	*cmd;
	t_cmd	*cur_cmd;
	t_token	*token;
	token_type type;
	char	**temp;
	int		i;

	token = NULL;
	cmd = NULL;
	while(*h_input)
	{
		i = 0;
		add_cmd(&cmd, &token);
		if (!cur_cmd) 
			cur_cmd = cmd;
		temp = ft_split(*h_input, ' ');
		while(temp[i])

		{
			type = get_type(temp[i]);
			add_token(&cmd->token, temp[i], type);
			i++;
		}
		ft_print_array(temp);
		free_array(temp);
		h_input++;
		cmd = cmd->next;
	}
	printf("teste");
	//REMOVER É APENAS PARA TESTAR 
	//tentar imprimir e entender o porque não está funcionando a impressão 
	//achoooo que é isso 
	t_cmd *tmp = cur_cmd;
	while (tmp)
	{
 		if (tmp->token)
		{
			printf("T_CMD input -> %s\n", tmp->token->input);
			t_token *bla = tmp->token;
			while (bla != NULL)
			{
				printf("T_TOKEN input -> %s\n", bla->input);
				printf("T_TOKEN type -> %i\n", bla->type);
				bla = bla->next;
			}
		}
		tmp = tmp->next;
	}

}
void	handle_input(char *input)
{
	//t_token *tokens;
	char **h_input;
	//int i;

	//tokens = NULL;

	h_input = ft_split(input, '|');
	ft_print_array(h_input);
	get_tokens(h_input);

}