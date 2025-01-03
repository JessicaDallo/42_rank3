/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:44:11 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/02 23:00:42 by sheila           ###   ########.fr       */
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

char	**convert_args(t_minishell *mshell, t_token *token)
{
	char	**temp;
	int 	i;
	
	temp = (char **)malloc(sizeof(char *) * (ft_arraylen(mshell, token) + 1));
	if (!temp)
		return (NULL);
	i = 0;
	temp[i++] = ft_strdup(token->input);
	while (token)
	{
		if(token->type == ARG)
		{
			handle_expansions(mshell, &token->input, 0);
			if(!token->input || !*token->input) 
			{
				token = token->next;
				continue;
			}
			temp[i] = ft_strdup(handle_quotes(token->input, 0, 0));
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

/*char	**convert_args(t_minishell *mshell, t_token *token)
{
	char	**temp;
	int 	i;
	
	temp = (char **)malloc(sizeof(char *) * (ft_arraylen(mshell, token) + 1));
	if (!temp)
		return (NULL);
	i = 0;
	temp[i++] = strdup(token->input);
	while (token)
	{
		if(token->type == ARG)
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
}*/

