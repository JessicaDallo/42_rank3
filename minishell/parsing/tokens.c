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

int	ft_count_words(char *arg, char c)
{
	int count = 0;
	int was_cmd = 0;

	while (*arg)
	{
	// Pula os delimitadores (espaços)
	while (*arg == c)
	{
		was_cmd = 0;
		arg++;
	}
	// Se o caractere atual não for um delimitador e não estivermos dentro de um comando, contamos um novo comando/palavra
	if (*arg && (*arg != '<' && *arg != '>') && !was_cmd &&  *arg != '|')//o pipe entra aqui 
	{
		count++;
		was_cmd = 1;  // Estamos dentro de um comando
	}
	// Se o caractere for um delimitador especial (|, <, >), ele encerra o comando atual
	if (*arg == '|' || *arg == '<' || *arg == '>')
	{
		if((*(arg + 1) != '<' && *(arg + 1) != '>') || *arg == '|')//o pipe entra aqui tbm 
			count++;
		was_cmd = 0; // Estamos fora de um comando
	}
	// Avança para o próximo caractere
	if (*arg)
		arg++;
	}
	return count;
}



void	get_tokens(char *arg)
{
	t_token *token;
	char **cmd;
	int len_token;

	len_token = 0;
	len_token = ft_count_words(arg, ' ');
	printf("%d -> numeros de palavras \n", len_token);
	cmd = ft_calloc(sizeof(char *), len_token);
	if(!cmd)
		return ;
	cmd = find_cmd(arg, cmd);
	int i = 0;
	while(cmd[i])
	{
		printf("%s ->array\n",cmd[i]);
		i++;
	}
	i = 0;
	token = create_token(cmd[i]);
	while (cmd[++i] != NULL)
	{
		add_token(&token, cmd[i]);
	}
	t_token *temp = token;
	while(temp)
	{
		printf("token value -> %s\n",temp->value);
		temp = temp->next;
	}
}