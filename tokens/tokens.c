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

int	quote_count(char *str, char c)
{
	int i;

	i= 0;
	i++;
	while (str[i] != c)
	{
		i++;
	}
	i++;
	return (i);
}

bool	delimiter(char **str)
{
	if (**str == '|' || **str == '>' || **str == '<' || **str == '\n')
	{
		if (*(*str + 1 )== '<' || *(*str) + 1 == '>')
			(*str)++;
		return (true);
	}
	return (false);
}

int ft_count_words(char *s, char c)
{
	int	i;
	char quots;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
        {
			i++;
        }
    	while (*s && *s != c)
	    {
			if(*s == '"' || *s == '\'')
			{
				quots = *s;
				s++;
				while(*s && *s != quots)
					s++;
			}
			s++;
		}	
	}
	return (i);
}

char **ft_split_quots(char *str, char c)
{
	int i = 0;
	int start;
	int j = 0;
	char **splited;

	start = i;
	int len;
	len = ft_strlen(str);
	splited = ft_calloc(sizeof(char *), ft_count_words(str, c) + 1); ///a qui
	if(!splited)
		return (NULL);
	while(str[i] != '\0')
	{
		if(str[i] == '"' || str[i] == '\'')
		{
			i = i + quote_count(&str[i], str[i]);
			if(str[i] == c)
			{
				splited[j++] = ft_strndup(&str[start], i - start);// aqui 
				start = i + 1;
			}
		}
		else if (str[i] == c)
		{
			if (i > start)
				splited[j++] = ft_strndup(&str[start], i - start); //aqui VERIFICAR SE O TAMANHO PASSADO É O CORRETO 
			start = i + 1;
		}
		if(i < len )
			i++;
		else
			break ;
	}
	if (start < i)
		splited[j++] = ft_strndup(&str[start], i - start);
	splited[j] = NULL;
	return (splited);
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
		temp = ft_split_quots(*h_input, ' ');
		while(temp[i])
		{
			type = get_type(temp[i], teste);
			if(is_delimiter(temp[i]))
				i++;
			add_token(&cmd, temp[i], type, teste);
			teste = false;
			i++;
		}
		h_input++;
		ft_print_array(temp);
		free_array(temp);
		temp = NULL;
	}
	ft_print_tokens(&cmd);
	free_array(temp);
	free_cmd(cmd);
}
void	parse_input(char *input)
{
	char **h_input;

	h_input = ft_split_quots(input, '|');
	get_tokens(h_input);
	free_array(h_input);

}
