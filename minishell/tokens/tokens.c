/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:33:08 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 15:33:08 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/include_builtins.h"

char	**find_cmd(char *arg, char **cmd)
{
	static int init = 0;
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
			cmd[j++] = ft_strndup(&arg[init], i - init);
			init = i;
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
			i++;
		}
		else if (*arg && !delimiter(&arg) && !was_cmd)
		{
			i++;
			was_cmd = 1;
		}
		else if (delimiter(&arg))
		{
			if (*arg == '|')
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
	char **cmd;
	int len_token;
	int	i;

	len_token = 0;
	len_token = ft_count_words(arg, ' ');
	cmd = ft_calloc(sizeof(char *), len_token);
	if(!cmd) 
		return ;
	cmd = find_cmd(arg, cmd);
	i = 0;
	while(cmd[i])
	{
	
		printf("%s ->array\n",cmd[i]);
		i++;
	}
	// i = 0;
	// token = NULL;
	// while (cmd[i] != NULL)
	// {
	// 	type = get_type(cmd[i]);
	// 	if (ft_strcmp(cmd[i], "<") == 0 || ft_strcmp(cmd[i], ">") == 0 || ft_strcmp(cmd[i], "<<") == 0 || ft_strcmp(cmd[i], ">>") == 0)
	// 		i++;
	// 	add_token(&token, cmd[i], type);
	// 	i++;
	// }

	i = 0;
	int	flg = 0;
	int j = 0;
	token = NULL;
	while (cmd[i])
	{
		type = get_type(cmd[i]);
		if (ft_strcmp(cmd[i], "<") == 0 || ft_strcmp(cmd[i], ">") == 0 || ft_strcmp(cmd[i], "<<") == 0 || ft_strcmp(cmd[i], ">>") == 0)
			i++;
		add_token(&token, cmd[i], type);
		if(ft_strcmp(cmd[i], "export") == 0)
		{
			i++;
			handle_value(cmd, &token);
			while(!is_delimiter(cmd[i]))
			{
				token->value[j] = ft_calloc(sizeof(char), ft_strlen(cmd[i] + 1));
				token->value[j] = cmd[i];
				j++;
				i++;
				flg = 1;
			}
		}
//	verificar sem funcao de aspas e ver como o rpogrmam se comporta

		if(cmd[i] == NULL)
					break ;
		if(flg)
		{
			flg = 0;
			continue ;
		}
		i++;
	}

	t_token *temp = token;
	// while(temp)
	// {
	// 	i = 0;
	// 	if (!temp->value)
	// 	{
	// 		printf("temp->value is NULL.\n");
	// 		// break; // ou continue, dependendo da lógica.
	// 	}
	// 	while(temp->value[i])
	// 	{
			
	// 		printf("token value -> %s \n", temp->value[i]);
	// 		i++;
	// 	}
	// 	printf("token name -> %s\ntoken type -> %d\n",temp->name, temp->type);
	// 	if (!temp->next)
	// 	{
   	// 		 printf("Reached end of list or temp->next is NULL.\n");
   	// 		 break;
	// 	}
	// 	temp = temp->next;
	// }
	while(temp)
	{
		if (temp->value != NULL)
		{
 		   i = 0;
 	  	 while (temp->value[i] != NULL)
  		  {
  		      printf("token value -> %s\n", temp->value[i]);
  	 	     i++;
  		  }
		}
		else
		{
 		   printf("temp->value is NULL\n");
		}
		printf("token name -> %s\ntoken type -> %d\n",temp->name, temp->type);
		temp = temp->next;
	}
}
