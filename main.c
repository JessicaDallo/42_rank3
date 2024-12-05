/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:33:59 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 14:34:42 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/include_builtins.h"
 //
/*int main(int argc, char **argv, char **envp)
{
    t_minishell mshell;
	
    (void)argc;
    init_struct(&mshell, envp);
    check_syntax(argv);
   
   return 0;
}*/

/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft/libft.h"

// Função para reproduzir o comportamento do echo
void    handle_input(char c, char **output, int s_quote, int d_quote)
{
    char    *aux;
    char    temp[2];
    if (c == ' ' && !s_quote && !d_quote)
    {
        //if (*output[ft_strlen(*output) - 1] != ' ')
        if (ft_strlen(*output) > 0 && (*output)[ft_strlen(*output) - 1] != ' ')
        {
            aux = ft_strjoin(*output, " ");
            free(*output);
            *output = aux;
        }
    }
    else
    {
        temp[0] = c;
        temp[1] = '\0';
        aux = ft_strjoin(*output, temp);
        free(*output);
        *output = aux;
    }
    return;
}

char    *handle_quotes(char *str, int s_quote, int d_quote)
{
    int i;
    size_t  len;
    char    *output;
    
    i = -1;
    len = ft_strlen(str);
    output = ft_strdup("");
    if (!output)
       return NULL;
    while(++i < len)
    {
        if (str[i] == '\'' && !d_quote)
            s_quote = !s_quote;
        else if (str[i] == '"' && !s_quote)
            d_quote = !d_quote;
        else
            handle_input(str[i], &output, s_quote, d_quote);
    }
    return(output);
}

int main(void) {
    char input[256];
    char *result;

    printf("Digite uma string para o echo: ");
    if (!fgets(input, sizeof(input), stdin)) {
        perror("Erro ao ler entrada");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0'; // Remove o '\n'

    result = handle_quotes(input, 0, 0);

    if (result) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}*/


//char *process_input(char *input, int s_quote, int d_quote)
//{
//    char *output; // Resultado final
//    char *temp = NULL;
//    size_t len = strlen(input);
//    size_t i = -1;

//    if (!output)
//        return NULL;

//    while(++i < len)
//    {
//        if (input[i] == '\'' && !d_quote) {
//            s_quote = !s_quote;
//        } else if (input[i] == '"' && !s_quote) {
//            d_quote = !d_quote;
//        } else if (input[i] == ' ' && !s_quote && !d_quote)
//        {
//            if (output[strlen(output) - 1] != ' ')
//            {
//                temp = ft_strjoin(output, " ");
//                free(output);
//                output = temp;
//            }
//        }
//        else
//        {
//            char temp_char[2] = {input[i], '\0'};
//            temp = ft_strjoin(output, temp_char);
//            free(output);
//            output = temp;
//        }
//    }
//    // Verificar se aspas estão balanceadas
//    if (s_quote || d_quote) {
//        fprintf(stderr, "Erro: aspas não balanceadas.\n");
//        free(output);
//        return NULL;
//    }

//    return output;
//}

int main ()
{
	char	*input = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if(*input)
			add_history(input);

		printf("%s\n", input);
		
		if (validate(&input) > 0)
			continue;
		handle_input(input);
	}
}

