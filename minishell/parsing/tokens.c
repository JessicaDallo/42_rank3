#include "../include/minishell.h"

char	**find_cmd(char *arg, char **cmd)
{
	static int init = 0;
	int	i;
	int	j;

	i = init;
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

int	count(char **arg, char c)
{
	static int i = 0;
	static int was_cmd = 0;

	while (**arg == c)
	{
		was_cmd = 0;
		(*arg)++;
	}
	if (**arg && (**arg != '<' && **arg != '>') && !was_cmd &&  **arg != '|')
	{
		i++;
		was_cmd = 1;
	}
	if (**arg == '|' || **arg == '<' || **arg == '>')
	{
		if((*(*arg + 1) != '<' && *(*arg + 1) != '>') || **arg == '|')
			i++;
		was_cmd = 0;
	}
	return (i);
}

int	ft_count_words(char *arg, char c)
{
	static int len_word = 0;

	while (*arg)
	{
		//if (*arg == '"' || *arg == '\'')

		len_word = count(&arg, c);
		if (*arg)
			arg++;
	}
	return (len_word);
}

void	get_tokens(char *arg)
{
	t_token *token;
	char **cmd;
	int len_token;
	token_type type;

	len_token = 0;
	len_token = ft_count_words(arg, ' ');
	printf("%d -> numeros de palavras \n", len_token);
	cmd = ft_calloc(sizeof(char *), len_token);
	if(!cmd) 
		return ;
	cmd = find_cmd(arg, cmd);
	int i = 0;
	//essa parte não é necessária
	while(cmd[i])
	{
	
		printf("%s ->array\n",cmd[i]);
		i++;
	}
	i = 0;
	token = NULL;
	while (cmd[i] != NULL)
	{
		type = get_type(cmd[i]);
		if (ft_strcmp(cmd[i], "<") == 0 || ft_strcmp(cmd[i], ">") == 0 || ft_strcmp(cmd[i], "<<") == 0 || ft_strcmp(cmd[i], ">>") == 0)
			i++;
		add_token(&token, cmd[i], type);
		i++;
	}
	ft_free_array(cmd);
	t_token *temp = token;
	while(temp)
	{
		printf("token value -> %s\n tokentype -> %d\n",temp->value, temp->type);
		temp = temp->next;
	}
	ft_free_token(&token);
}