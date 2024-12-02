/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:33:29 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 15:33:29 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include_builtins.h"

int	val_sintax(char *arg)
{
	int	was_cmd;

	was_cmd = 0;
	while (*arg)
	{
		if (*arg == '|')
		{
			if(!val_pipe(&arg, was_cmd) || !was_cmd)
				return (printf("ERROR pipe\n"));
		}
		if (*arg == '>')
		{
			if(!val_red(&arg, was_cmd))
				return (printf("ERROR redir\n"));
		}
		if (*arg == '<')
		{
			if(!val_red_in(&arg, was_cmd))
				return (printf("ERROR redir\n"));
		}
		if (*arg == '"' || *arg == '\'')
		{
			if(!val_quot(&arg))
				return (printf("ERROR quotation\n"));
		}
		if(*arg != ' ')
			was_cmd = 1;
		arg++;
	}
	return (0);
}

int validate(char **input)
{
	if(!*input)
		return (1);
	*input = eup_str(*input);
	return (val_sintax(*input));
}
