/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:33:08 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 15:33:08 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include_builtins.h"

bool is_delimiter(char *arg)
{
	if(ft_strcmp(arg, "|") == 0 || ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<") == 0 || !arg)
		return (true);
	return (false);
}

int len_array(char **arg)
{
	int i = 0;
	while(!is_delimiter(arg[i]))
		i++;
	return (i);
}

//faz o malloc na estrutura token->value
void  handle_value(char **arg, t_token **token)
{
	while(ft_strcmp(*arg, "export") == 1)
		arg++;
	arg++;
	printf("%s -> handle value\n", *arg);
	int len = len_array(arg);
	printf("%d LEN HANDLE\n",len);
	if ((*token)->value == NULL)
		(*token)->value = ft_calloc(sizeof(char *), len);
}






















void	ft_print_tokens(t_token *token)
{
	t_token *temp = token;
		while (temp)
		{
			printf("token name -> %s\n", temp->name);
			if (temp->value != NULL)
			{
				int j = 0;
				while (temp->value[j])
				{
					printf("token value -> %s\n", temp->value[j]);
					j++;
				}
			}
		temp = temp->next;
		}
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