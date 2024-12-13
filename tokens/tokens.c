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

static char **check_and_split(char *h_input, char **temp)
{
	//char **temp;
	int len_token;

	len_token = 0;
	len_token = ft_count_words(h_input, ' ');
	printf("QUAL TAMANHO %d \n", len_token),
	temp = ft_calloc(sizeof(char *), len_token);
	if(!temp) 
		return NULL;
	return(find_cmd(h_input, temp));
}

char	**find_cmd(char *arg, char **cmd)
{
	int init = 0;
	int	i;
	int	j;

	i = init;
	j = 0;
	while(arg[i])
	{
		if(arg[i] == '"' || arg[i] == '\'')
		{
			i = i + quote_count(&arg[i], arg[i]);
			if(arg[i] == ' ' || delimiter(&arg) || arg[i] == '"' || arg[i] == '\'')
			{
				cmd[j++] = ft_strndup(&arg[init], i - init);
				init = i;
			}
		}
		else if (arg[i] == ' ')
		{
			if (i > init)
				cmd[j++] = ft_strndup(&arg[init], i - init);
			init = i + 1;
		}
		i++;
	}
	if (init < i)
		cmd[j++] = ft_strndup(&arg[init], i - init);
	cmd[j] = NULL;
	return (cmd);
}

int	quote_count(char *arg, char c)
{
	int i;

	i= 0;
	i++;
	while (arg[i] != c)
	{
		i++;
	}
	i++;
	return (i);
}

bool	delimiter(char **arg)
{
	if (**arg == '|' || **arg == '>' || **arg == '<' || **arg == '\n')
	{
		if (*(*arg + 1 )== '<' || *(*arg) + 1 == '>')
			(*arg)++;
		return (true);
	}
	return (false);
}

void	quote_pointer(char **arg, char c)
{
	int i;
	
	i = 0;
	(*arg)++;
	while(**arg != c)
	{
		i++;
		(*arg)++;
	}
}

int	ft_count_words(char *arg, char c)
{
	int i;
	int was_cmd;

	i = 0;
	was_cmd = 0;
	while (*arg)
	{
		// while (*arg == c)
		// {
		// 	was_cmd = 0;
		// 	arg++;
		// }
		if(*arg == '"' || *arg == '\'')
		{
			quote_pointer(&arg, *arg);
			if(*arg == ' ' || *arg == '"' || *arg == '\'')
				i++;
			arg++;
		}
		else if (*arg != c && was_cmd == 0)
		{
			was_cmd = 1;
			i++;
		}
		else if (*arg == c)
			i++;
		// else if (*arg && !delimiter(&arg) && !was_cmd)
		// {
		// 	i++;
		// 	was_cmd = 1;
		// }
		// else if (delimiter(&arg))
		// {
		// //	if (*arg == '|')
		// 		i++;
		// 	was_cmd = 0;
		// }
		if (*arg == '\0')
			return i;
		arg++;
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
		temp = check_and_split(*h_input, temp);
		ft_print_array(temp);
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
		free_array(temp);
		h_input++;
	}
	//REMOVER É APENAS PARA TESTAR 
	ft_print_tokens(&cmd);
}
void	parse_input(char *input)
{

	char **h_input;

	h_input = ft_split(input, '|');
	ft_print_array(h_input);
	get_tokens(h_input);
}
