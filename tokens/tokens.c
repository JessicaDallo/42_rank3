/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:49:28 by jesilva-          #+#    #+#             */
/*   Updated: 2024/11/27 09:49:32 by jesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include_builtins.h"

char	**find_cmd(char *arg, char **cmd)
{
	int init = 0;
	int	i;
	int	j;

	i = init;
	j = 0;
	while(arg[i])
	{
		if(arg[i] == '|' || arg[i] == '<' || arg[i] == '>')
		{
			if(i > init)
			{
				cmd[j++] = ft_strndup(&arg[init], i - init);
			}
			if((arg[i] == '<' && arg[i +1 ] == '<') || (arg[i] == '>' && arg[i +1 ] == '>'))
			{
				cmd[j++] = ft_strndup(&arg[i], 2);
				init = i + 2;
				i++;
			}
			else 
			{
				cmd[j++] = ft_strndup(&arg[i], 1);
				init = i + 1;
			}
		}
		else if(arg[i] == '"' || arg[i] == '\'')
		{
			i = i + quote_count(&arg[i], arg[i]);
			if(*arg == ' ' || delimiter(&arg))
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
		while (*arg == c)
		{
			was_cmd = 0;
			arg++;
		}
		if(*arg == '"' || *arg == '\'')
		{
			quote_pointer(&arg, *arg);
			if(*arg == ' ' || delimiter(&arg))
				i++;
			arg++;
		}
		else if (*arg && !delimiter(&arg) && !was_cmd)
		{
			i++;
			was_cmd = 1;
		}
		else if (delimiter(&arg))
		{
		//	if (*arg == '|')
				i++;
			was_cmd = 0;
		}
		if (arg)
			arg++;
	}
	return (i);
}


void	get_tokens(char *arg)
{
	token_type type;
	t_token *token;
	t_token *temp;
	char **cmd;
	int len_token;
//	int	i;

	len_token = 0;
	len_token = ft_count_words(arg, ' ');
	cmd = ft_calloc(sizeof(char *), len_token);
	if(!cmd) 
		return ;
	cmd = find_cmd(arg, cmd);
	//print se split foi feito corretamente 
	ft_print_array(cmd);
	//i = 0;
	int	flg = 0;
	int j = 0;
	token = NULL;
	//cria a lista de tokens
	while (*cmd)
	{
		type = get_type(*cmd);
		if (ft_strcmp(*cmd, "<") == 0 || ft_strcmp(*cmd, ">") == 0 || ft_strcmp(*cmd, "<<") == 0 || ft_strcmp(*cmd, ">>") == 0)
			cmd++;
		temp = add_token(&token, *cmd, type);
		if(type == PIPE)
		{
			cmd++;
			continue;
		}
		if(type == CMD)
		{
			cmd++;
			//adiciona array token->value 
			handle_value(cmd, &temp, *cmd);
			while(!is_delimiter(*cmd))
			{
				temp->value[j] = ft_strdup(*cmd);
				j++;
				cmd++;
				flg = 1;
				//temp->value[j] = NULL;
			}
		temp->value[j] = NULL;
		}
		if(*cmd == NULL)
					break ;
		if(flg || is_delimiter(*cmd))
		{
			flg = 0;
			j = 0;
			continue ;
		}
		cmd++;
	}
	//print se tokens foi feito corretamente.
	temp = token;
		while (temp)
		{
			printf("token name -> %s\n", temp->name);
			printf("token type -> %d\n", temp->type);
			if (temp->value != NULL)
			{
				int j = 0;
				while (temp->value[j])
				{
					printf("token value -> %s\n", temp->value[j]);
					j++;
				}
			}
		temp = temp->next;
		}
}

