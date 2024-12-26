/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:44:11 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/23 15:33:00 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	ft_arraylen(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
			i++;
		token = token->next;
	}
	return (i);
}

char	**convert_args(t_token *token)
{
    char	**temp;
    int 	i;
    int		len;

    len = ft_arraylen(token);    
    temp = (char **)malloc(sizeof(char *) * (len + 1));
    if (!temp)
        return (NULL);
    i = 0;
    while (token)
    {
		if(token->type == CMD || token->type == ARG)
		{
			temp[i] = strdup(token->input);
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


