/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:30 by sheila            #+#    #+#             */
/*   Updated: 2024/12/06 18:46:16 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	handle_expansions(t_minishell *mshell, char **line, int flag)
{
	expand_exit(mshell, line, flag);
	expand_var(mshell, line, flag);
}

bool is_expand(char *delim)
{
	if (ft_strchr(delim, '\''))
		return(false);
	else if (ft_strchr(delim, '\"'))
		return (false);
	else
	return(true);
}

char *get_epos(char *line, int flag)
{
	char	quote;
	
    while (*line)
    {
        if (flag && (*line == '\'' || *line == '\"'))
        {
        	quote = *line++;
            while (*line && *line != quote)
            {
                if (quote == '\"' && *line == '$' && *(line + 1) == '?')
                    return (line);
                line++;
            }
        }
        if (*line == '$' && *(line + 1) == '?')
            return (line);
        line++;
    }
    return (NULL);
}

void expand_exit(t_minishell *mshell, char **line, int flag)
{
    char 	*e_pos;
	char	*new_line;
	char	*temp;
	char	*exit;
		
	e_pos = get_epos(*line, flag);
	while (e_pos)
	{
		exit = ft_itoa(mshell->e_code);
        temp = ft_strjoin((ft_substr(*line, 0, e_pos - *line)), exit);
        new_line = ft_strjoin(temp, (e_pos + 2));
        free(temp);
        free(*line);
        *line = new_line;
		e_pos = get_epos(*line, flag);
    }
}

char *get_position(char *line, int flag)
{
    while (*line)
    {
        if (flag && (*line == '\'' || *line == '\"'))
        {
            char quote = *line++;
            while (*line && *line != quote)
            {
                if (quote == '\"' && *line == '$' && 
                    (ft_isalnum(*(line + 1)) || *(line + 1) == '_'))
                    return (line);
                line++;
            }
        }
        if (*line == '$' && (ft_isalnum(*(line + 1)) || *(line + 1) == '_'))
            return (line);
        line++;
    }
    return (NULL);
}

void update_line(char **line, char *value, char *str)
{
	char *new_line;
	char *temp;

	if (!(*line)[0] && !value)
		temp = ft_strdup("");
	else if (!(*line)[0] && value)
		temp = ft_strdup(value);
	else if (!value)
		temp = ft_strdup(*line);
	else
		temp = ft_strjoin(*line, value);
	new_line = ft_strjoin(temp, str);
	free(temp);
	free(*line);
	*line = new_line;
}

void expand_var(t_minishell *mshell, char **line, int flag)
{
    char *var_pos;
    char *key;
    char *value;
    int len;

    var_pos = get_position(*line, flag);
    while (var_pos)
	{
        len = 0;
        while (ft_isalnum(var_pos[len + 1]) || var_pos[len + 1] == '_')
            len++;
        key = ft_substr(var_pos, 1, len);
        *var_pos = '\0';
        value = get_value(mshell, key);
        update_line(line, value, var_pos + len + 1);
        free(key);
        var_pos = get_position(*line, flag);
    }
}

/*int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    t_minishell mshell;
    init_struct(&mshell, envp);

    char *line = strdup("");
	char input[256] = "END";
    mshell.e_code = 127;
    if (!line)
	{
        perror("Falha ao alocar memória para a linha");
        return EXIT_FAILURE;
    }
	printf("Digite uma string para o echo: ");
    if (!fgets(input, sizeof(input), stdin))
	{
        perror("Erro ao ler entrada");
        return 1;
    }
	line = input;
    printf("\nLinha original: %s\n", line);
    handle_expansions(&mshell, &line);
	char	*result = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!result)
	{
        perror("Falha ao alocar memória para a linha");
        return EXIT_FAILURE;
    }
	result = handle_quotes(line, 0, 0);
    printf("\nLinha expandida:%s\n", result);
    //free(line);
	free(result);
    return EXIT_SUCCESS;
}*/

/*int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    //int i = 0;
    init_struct(&mshell, envp);
    char *teste = ft_strdup("DUPLA \"$USER\" - SIMPLES '$USER' - EXIT_CODE $? - SEM_ASPAS $USER - MIX \"\'$USER\'\"");
    
    printf("\n--- Antes da expansao ---\n, %s\n", teste);
    handle_expansions(&mshell, &teste, 1);
    printf("\n--- Após o expansao ---\n, %s\n", teste);
}*/