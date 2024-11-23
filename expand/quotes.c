/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:39:57 by sheila            #+#    #+#             */
/*   Updated: 2024/11/22 16:49:37 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void    handle_input(char c, char **output, int s_quote, int d_quote)
{
    char    *aux = ft_strdup("");
	//char	*test = ft_strdup("");
	
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
		//test = ft_appendchar("_", c);
		//aux = ft_strjoin(*output, test);
        aux = ft_appendchar(*output, c);
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