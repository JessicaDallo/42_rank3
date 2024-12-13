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

static char **check_and_split(char *h_input, char c)
{
	char **temp;

	int len_token;

	len_token = 0;
	len_token = ft_count_words(h_input, c);
	printf("QUAL TAMANHO %d \n", len_token),
	temp = ft_calloc(sizeof(char *), len_token);
	if(!temp) 
		return NULL;
	return(find_cmd(h_input, temp));
}

int ft_count_words (char *h_input, char c)
{
	int	i;
	char quots;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if(*s == '"' || *s == '\'')
		{
			quots = *s;
			while(*s != quots)
				s++;
			i++;
		}
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}


int	get_type(char *cmd, bool teste)
{
	if(teste == true && !is_delimiter(cmd))
		return CMD;
	else if(ft_strcmp(cmd, ">") == 0)
		return OUTPUT_REDIR;
	else if (ft_strcmp(cmd, ">>") == 0)
		return APPEND_REDIR;
	else if(ft_strcmp(cmd, "<") == 0)
		return INPUT_REDIR;
	else if(ft_strcmp(cmd, "<<") == 0)
		return HEREDOC;
	else 
		return ARG;
}

void get_tokens(char **h_input)
{
	token_type type;
	t_cmd	*cmd;
	char	**temp;
	int		i;
	bool	teste;

	cmd = NULL;
	while(*h_input)
	{
		add_cmd(&cmd);
		teste = true;
		i = 0;
		temp = check_and_split(*h_input, ' ');
	//	ft_print_array(temp);
		//else
		//temp = ft_split(*h_input, ' ');
		while(temp[i])
		{
			type = get_type(temp[i], teste);
			if(is_delimiter(temp[i]))
				i++;
			add_token(&cmd, temp[i], type, teste);
			teste = false;
			i++;
		}
		//REMOVER É APENAS PARA TESTAR
		h_input++;
	}
	//REMOVER É APENAS PARA TESTAR 
	ft_print_tokens(&cmd);
	free_array(temp);
}
void	parse_input(char *input)
{

	char **h_input;

	//h_input = ft_split(input, '|');
	h_input = check_and_split(input, '|');
	ft_print_array(h_input);
	get_tokens(h_input);
}
