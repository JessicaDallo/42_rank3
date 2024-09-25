#include "include/minishell.h"

//ls -l | wc -c > teste.txt

// Função que encontra os comandos e tokens
char **find_cmd(char *arg, char **cmd)
{
	static int init = 0;
	int i = init;
	int j = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '|' || arg[i] == '<' || arg[i] == '>')
		{
			if (i > init)
				cmd[j++] = ft_strndup(&arg[init], i - init);
			if((arg[i] == '<' && arg[i+1] =='<') || ((arg[i] == '>' && arg[i+1] =='>')))
			{
				cmd[j++] = ft_strndup(&arg[i], 2);
				init = i + 2;
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
	return cmd;
}

int ft_count_words(const char *s, char c)
{
    int i;
    int isCommand = 0;
    int previousDelimiter = 0;

    i = 0;
    while (*s)
    {
	// Pula os espaços
	while (*s == c){
	    isCommand = 0;
	    previousDelimiter = 0;
	    s++;
	}

	// Se encontrar um caractere não separador, inicia uma nova palavra/comando
	if (*s) {
	    if (!isCommand && !(*s == '|' || *s == '<' || *s == '>')) {
		i++;
		isCommand = 1;
		previousDelimiter = 0;
	    }
	}

	// Reseta o isCommand se encontrar delimitadores especiais
	if (*s == '|' || *s == '<' || *s == '>') {
	    if(!previousDelimiter){
		i++;  // Conta como um comando separado
		previousDelimiter = 1;
		isCommand = 0;
	    }
	}

	// Move para o próximo caractere
	if (*s)
	    s++;
    }
    return (i);
}

void get_tokens(char *arg)
{
	int	len_token;
	char	**cmd;

	len_token = 0;
	arg = eup_str(arg);
	len_token = ft_count_words(arg, ' ');
	printf("%i -> quantidade de tokens\n", len_token);
	cmd = ft_calloc(sizeof(char *), len_token + 1);
	if(!cmd)
		return ;
	cmd = find_cmd(arg, cmd);
	int i = 0;
	while(cmd[i])
	{
		printf("%s\n",cmd[i]);
		i++;
	}
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);

}

// 	// Alocação de memória para o array de tokens
// 	char **cmd = malloc(sizeof(char *) * (token_count + 2)); // Adiciona espaço extra para NULL

// 	if (!cmd)
// 	{
// 		ft_printf("Erro ao alocar memória\n");
// 		return;
// 	}

// 	cmd = find_cmd(arg, cmd); // Preenche o array com tokens

// 	int i = 0;
// 	while (cmd[i]) // Imprime os tokens
// 	{
// 		ft_printf("Token %d: %s\n", i, cmd[i]);
// 		i++;
// 	}

// 	// Libera a memória alocada para os tokens
// 	i = 0; 
// 	while (cmd[i])
// 	{
// 		free(cmd[i]);
// 		i++;
// 	}
// 	free(cmd);
// }