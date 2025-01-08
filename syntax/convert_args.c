/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:44:11 by shrodrig          #+#    #+#             */
/*   Updated: 2025/01/07 19:53:45 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arraylen(t_minishell *mshell, t_token *token)
{
	int	i;

	i = 0;
	(void)mshell;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
		{
			//handle_expansions(mshell, &token->input, 0);
			i++;
		}
		token = token->next;
	}
	return (i);
}

void	expand_args(t_minishell *mshell, t_token *token)
{
	t_token	*tmp;

	if (!token || !token->input)
		return ;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			handle_expansions(mshell, &tmp->input, 0);
		tmp = tmp->next;
	}
	g_e_code = 0;
}

char	**convert_args(t_minishell *mshell, t_token *tk)
{
	char	**temp;
	int		i;

	temp = (char **)malloc(sizeof(char *) * (ft_arraylen(mshell, tk) + 1));
	if (!temp)
		return (NULL);
	i = 0;
	if (!ft_strncmp(tk->input, "\"\"", 3) || !ft_strncmp(tk->input, "\'\'", 3))
	{
		temp[i++] = ft_strdup(tk->input);
		tk = tk->next;
	}
	while (tk)
	{
		if (tk->input && *tk->input)
		{
			temp[i] = handle_quotes(tk->input, 0, 0);
			if (!temp[i])
			{
				free_array(temp);
				return (NULL);
			}
			i++;
		}
		tk = tk->next;
	}
	temp[i] = NULL;
	return (temp);
}
