/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:39:57 by sheila            #+#    #+#             */
/*   Updated: 2024/12/02 15:34:20 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

/*char	*rm_space(char *str)
{
    int len = strlen(str);
    char *result = (char *)malloc(len + 1);
    bool inside_quotes = false;
    char quote_char = '\0';
    int j = 0;
    int i = -1;
    
    while (++i < len)
    {
        char current = str[i];
        
        if (current == '\'' || current == '\"')
        {
            if (inside_quotes && current == quote_char)
            {
                inside_quotes = false;
                quote_char = '\0';
            }
            else if (!inside_quotes)
            {
                inside_quotes = true;
                quote_char = current;
            }
            result[j++] = current;
        }
        else if (inside_quotes)
            result[j++] = current;
        else
        {
            if (current != ' ' || (j > 0 && result[j - 1] != ' '))
                result[j++] = current;
        }
    }
    result[j] = '\0';
	return(result);
}*/

void process_char(char current, char *result, t_var *aux)
{
    if (current == '\'' || current == '\"')
    {
        if (aux->is_val && current == aux->c)
        {
            aux->is_val = false;
            aux->c = '\0';
        } else if (!aux->is_val)
        {
            aux->is_val = true;
            aux->c = current;
        }
        result[aux->i++] = current; // Copia o caractere de aspas
    }
    else if (aux->is_val)
        result[aux->i++] = current; // Copia tudo dentro de aspas
    else 
    {
        if (current != ' ' || (aux->i > 0 && result[aux->i - 1] != ' '))
            result[aux->i++] = current; // Remove espaços extras
    }
}

char *rm_space(char *str)
{
    int     len;
    char    *result;
    t_var  *aux;
    int     size;
    
    len = strlen(str);
    result = (char *)malloc(len + 1);
    if (!result)
        return(NULL);
    aux = malloc(sizeof(t_var));
    aux->is_val = false;
    aux->c = '\0';
    size = -1;
    while (++size < len) 
        process_char(str[size], result, aux);
    result[aux->i] = '\0';
    return result;
}

void    handle_input(char c, char **output)
{
    char    *aux;
	
    aux =  ft_strdup("");
    aux = ft_appendchar(*output, c);
	printf("Caractere c: %c\n", c);
    free(*output);
    *output = aux;
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
    temp = (char *)malloc(sizeof(char) * (len + 1));
    output = ft_strdup("");
    if (!output || !temp)
       return NULL;
    temp = rm_space(str);
   //printf("\nREMOVE:%s\n", temp);
    //printf("\nBEFORE_OUT:%s\n", output);
    len = (int)ft_strlen(temp);
    while(++i < len)
    {
        if (temp[i] == '\'' && !d_quote)
            s_quote = !s_quote;
        else if (temp[i] == '"' && !s_quote)
            d_quote = !d_quote;
        else
            handle_input(temp[i], &output);
            //handle_input(temp[i], &output, s_quote, d_quote);
    }
    printf("\nOUT:%s\n", output);
    return(output);
}

/*int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    t_minishell mshell;
    init_struct(&mshell, envp);

    //char *line = strdup("");
	char input[256] = "\'\"END\"\'";
    mshell.e_code = 127;
	//line = input;
    //printf("\nLinha original: %s\n", input);
    //handle_expansions(&mshell, &input);
	char	*result = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!result)
	{
        perror("Falha ao alocar memória para a linha");
        return EXIT_FAILURE;
    }
	result = handle_quotes(input, 0, 0);
    printf("\nLinha expandida:%s\n", result);
    //free(line);
	free(result);
    return EXIT_SUCCESS;
}*/