/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:44:11 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/01 23:40:45 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	ft_arraylen(t_minishell *mshell, t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
		{
			handle_expansions(mshell, &token->input, 0);
			i++;
		}
		token = token->next;
	}
	return (i);
}

char	**convert_args(t_minishell *mshell, t_token *token) // checar linhas
{
	char	**temp;
	int 	i;
	int		len;

	len = ft_arraylen(mshell, token);
	temp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (token)
	{
		if(token->type == CMD || token->type == ARG)
		{
			handle_expansions(mshell, &token->input, 0);
			temp[i] = strdup(handle_quotes(token->input, 0, 0));
			if (!temp[i])
			{
		   		free_array(temp);
				return (NULL);
			}
			i++;
		}
		token = token->next;
	}
	temp[i] = NULL;
	return (temp);
}


