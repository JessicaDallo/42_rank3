/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:39:57 by sheila            #+#    #+#             */
/*   Updated: 2024/12/06 18:29:38 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

bool process_char(char current, char *prev, char *result, bool *inside_quotes)
{
    static char quote_char;
   
    quote_char = '\0';
    if (current == '\'' || current == '\"') // Verifica se o caractere é uma aspa
    {
        if (*inside_quotes && current == quote_char)
        {
            *inside_quotes = false;
            quote_char = '\0';
        }
        else if (!*inside_quotes)
        {
            *inside_quotes = true;
            quote_char = current;
        }
        *result = current; // Copia o caractere de aspas
        return (true);
    }
    if (*inside_quotes || (current != ' ' || (prev && *prev != ' ')))
    {
        *result = current; // Copia o caractere
        return (true);
    }
    return (false);
}

char	*rm_space(char *str)
{
    char    *result;
    char    prev;
    bool    inside_quotes;
    size_t  j = 0;
    size_t  i = 0;
    
    result = (char *)malloc(ft_strlen(str) + 1);
    if(!result)
        return(NULL);
    j = 0;
    i = 0;
    inside_quotes = false;
    while (str[i])
    {
        if (i > 0)
            prev = result[j - 1];
        else
            prev = '\0';
        if (process_char(str[i], &prev, &result[j], &inside_quotes))
            j++;
        i++;
    }
    result[j] = '\0';
    return (result);
}

char    *handle_quotes(char *str, int s_quote, int d_quote)
{
    char    *output;
    char    *temp;
    char    *aux;
    size_t      i;
    
    output = ft_strdup("");
    temp = rm_space(str);
    i = -1;
    while(++i < (ft_strlen(temp)))
    {
        if (temp[i] == '\'' && !d_quote)
            s_quote = !s_quote;
        else if (temp[i] == '"' && !s_quote)
            d_quote = !d_quote;
        else
        {
            aux = ft_appendchar(output, temp[i]);    
            free(output);
            output = aux;
        }
    }
    free(temp);
    return(output);
}
