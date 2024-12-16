// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tokens_utils.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/27 09:49:43 by jesilva-          #+#    #+#             */
// /*   Updated: 2024/11/27 09:49:47 by jesilva-         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "../includes/include_builtins.h"

bool check_quots(char *h_input)
{
	int i = 0;
	while (h_input[i])
	{
		if(h_input[i] == '\'' || h_input[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

bool is_delimiter(char *arg)
{
	if(ft_strcmp(arg, "|") == 0 || ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0 || ft_strcmp(arg, "<<") == 0 || !arg)
		return (true);
	return (false);
}

void	ft_print_array(char **cmd)
{
	int i = 0;
	while(cmd[i])
	{
	
		printf("%s ->array\n",cmd[i]);
		i++;
	}
}
void ft_print_tokens(t_cmd **cmd)
{
	t_cmd *tmp = *cmd;
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
		if(tmp->next != NULL)
			tmp = tmp->next;
		else
			break;
	}
}
