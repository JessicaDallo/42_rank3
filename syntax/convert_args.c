/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:44:11 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/09 02:26:18 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arraylen(t_minishell *mshell, t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
		{
			handle_expansions(mshell, &token->input, 1);
			i++;
		}
		token = token->next;
	}
	g_e_code = 0;
	return (i);
}

bool	loop_convert_args(t_token *tk, int i, char **temp)
{
	while (tk)
	{
		if (tk->input && *tk->input)
		{
			temp[i] = handle_quotes(tk->input, 0, 0);
			if (!temp[i])
			{
				free_array(temp);
				return (false);
			}
			i++;
		}
		tk = tk->next;
	}
	temp[i] = NULL;
	return (true);
}

char	**convert_args(t_minishell *mshell, t_token *tk)
{
	char	**temp;
	int		i;

	temp = (char **)malloc(sizeof(char *) * (ft_arraylen(mshell, tk) + 1));
	if (!temp)
		return (NULL);
	if (!*tk->input && !tk->next)
	{
		free(temp);
		return (NULL);
	}
	i = 0;
	if (!ft_strncmp(tk->input, "\"\"", 3) || !ft_strncmp(tk->input, "\'\'", 3))
	{
		temp[i++] = ft_strdup(tk->input);
		tk = tk->next;
	}
	if (!loop_convert_args(tk, i, temp))
		return (NULL);
	return (temp);
}
