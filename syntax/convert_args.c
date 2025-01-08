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

// void	expand_args(t_minishell *mshell, t_token *token)
// {
// 	t_token	*tmp;

// 	if (!token || !token->input)
// 		return ;
// 	tmp = token;
// 	while (tmp)
// 	{
// 		if (tmp->type == CMD || tmp->type == ARG)
// 			handle_expansions(mshell, &tmp->input, 1);
// 		tmp = tmp->next;
// 	}
// 	g_e_code = 0;
// }

static int	process_conv_args(char ***temp, char *input, int i)
{
	*temp[i] = handle_quotes(input, 0, 0);
	if (!*temp[i])
	{
		free_array(*temp);
		return (0);
	}
	return (1);
}

char	**convert_args(t_minishell *mshell, t_token *tk)
{
	char	**temp;
	int		i;

	temp = (char **)malloc(sizeof(char *) * (ft_arraylen(mshell, tk) + 1));
	if (!temp)
		return (NULL);
	if (!*tk->input)
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
	while (tk)
	{
		if (tk->input && *tk->input)
		{
			if (!(process_conv_args(&temp, tk->input, i)))
				return (NULL);
			i++;
		}
		tk = tk->next;
	}
	temp[i] = NULL;
	return (temp);
}
