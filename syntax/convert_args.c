/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:44:11 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/17 22:09:23 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	ft_arraylen(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
			i++;
		token = token->next;
	}
	return (i);
}

char	**convert_args(t_token *token)
{
    char	**temp;
    int 	i;
    int		len;

    len = ft_arraylen(token);    
    temp = (char **)malloc(sizeof(char *) * (len + 1));
    if (!temp)
        return (NULL);
    i = 0;
    while (token)
    {
		if(token->type == CMD || token->type == ARG)
		{
			temp[i] = strdup(token->input);
        	if (!temp[i])
        	{
           		free_array(temp);
            	return (NULL);
        	}
			i++;
		}
        token = token->next;
    }
    temp[i] = NULL;
    i = 0;
    while (temp[i])
    {
        printf("ARG: %s\n", temp[i]);
        i++;
    }
    return (temp);
}

/*t_token *cr_token(token_type type, const char *input)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->input = strdup(input); // Copia o valor da string
    new_token->next = NULL;
    return new_token;
}

t_token *cr_sample_tokens()
{
    t_token *token1 = cr_token(token, "echo");
	t_token *token2 = cr_token(HEREDOC, "ola");
    t_token *token3 = cr_token(ARG, "\"\'$USER\'\"");
    t_token *token4 = cr_token(ARG, " \"   bom   \"");
    t_token *token5 = cr_token(INPUT_REDIR, "dia      ?");
	t_token *token6 = cr_token(ARG, "\' \"$PWD\" \'");

    // Conecte os tokens
    token1->next = token2;
    token2->next = token3;
	token3->next = token4;
    token4->next = token5;
	token5->next = token6;

    return token1; // Retorna o início da lista
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
	char **args;
	int i = 0;
    
    init_struct(&mshell, envp);
    
    t_token *tokens = cr_sample_tokens();

    printf("Antes de converter:\n");
    t_token *temp = tokens;
    while (temp)	//i = 0;
	// while (temp[i])
    // {
    //     printf("ARG: %s\n", temp[i]);
    //     i++;
    // }
    {
        printf("Token type: %d, input: %s\n", temp->type, temp->input);
        temp = temp->next;
    }

    args = convert_args(tokens);

    printf("\nDepois de converter\n");

    while (args[i])
    {
        printf("ARG: %s\n", args[i]);
        i++;
    }
    return 0;
}*/


