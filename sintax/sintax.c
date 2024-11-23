/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:37:11 by sheila            #+#    #+#             */
/*   Updated: 2024/11/22 13:24:49 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "include_builtins.h"

/*int	open_quotes(char *str)
{
	int	quotes;
	quotes = 0;
	while(*str)
	{
		if(*str == '\'' || *str == '\"')
			quotes++;
		str++;
	}
	return((quotes % 2));
}
	

char	*check_syntax(char	**input)
{
	int i;
	i = -1;
	while(input[++i])
	{
		if(open_quotes(input[i]))
			ft_putstr_fd("You forgot some quote open\n", STDOUT_FILENO);
	}
}

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <linux/limits.h>
#include <fcntl.h>
#include <stdbool.h> 
#include <signal.h>
#include <wait.h>


void    handle_input(char c, char **output, int s_quote, int d_quote)
{
    char    *aux;
	char	*test;
	
    if (c == ' ' && !s_quote && !d_quote)
    {
        //if (*output[ft_strlen(*output) - 1] != ' ')
        //if (ft_strlen(*output) > 0 && (*output)[ft_strlen(*output) - 1] != ' ')
        //{
            aux = ft_strjoin(*output, " ");
            free(*output);
            *output = aux;
        //}
    }
    else
    {
		test = ft_appendchar("_", c);
		aux = ft_strjoin(*output, test);
        //aux = ft_appendchar(*output, c);
		printf("Caractere c: %c\n", c);
        free(*output);
        *output = aux;
    }
    return;
}

char    *handle_quotes(char *str, int s_quote, int d_quote)
{
    int		i;
    int		len;
    char	*output;
    char    *temp;
    
    i = -1;
    len = (int)ft_strlen(str);
    output = (char *)malloc(sizeof(char) * (len + 1));
    temp = (char *)malloc(sizeof(char) * (len + 1));
    if (!output || !temp)
       return NULL;
    temp = eup_str(str);
    printf("\nEPUR:%s\n", temp);
    len = (int)ft_strlen(temp);
    while(++i < len)
    {
        if (temp[i] == '\'' && !d_quote)
            s_quote = !s_quote;
        else if (temp[i] == '"' && !s_quote)
            d_quote = !d_quote;
        else
            handle_input(temp[i], &output, s_quote, d_quote);
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

    result = handle_quotes(input, 0, 0);

    if (result)
	{
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