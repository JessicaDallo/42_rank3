/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:30 by sheila            #+#    #+#             */
/*   Updated: 2024/11/10 00:43:52 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

void	handle_expansions(t_minishell *mshell, char **line)
{
	printf("Iniciando handle_expansions com a linha: %s\n", *line);
	expand_exit(mshell, line);
	printf("Após expand_exit: %s\n", *line);
	expand_var(mshell, line);
	printf("Após expand_var: %s\n", *line);
}

char	*get_position(char *line)
{
	while (*line)
	{
		if (*line == '\'')
		{
			line++;
			while (*line && *line != '\'')
				line++;
		}
		if (*line == '\"')
		{
			line++;
			while (*line && *line != '\"')
			{
				if (*line == '$' && ((ft_isalnum(*(line + 1)) || *(line + 1) == '_') || *(line + 1) == '?'))
					return line;
				line++;
			}
		}
		if (*line == '$' && ((ft_isalnum(*(line + 1)) || *(line + 1) == '_') || *(line + 1) == '?'))
			return line;
		line++;
	}
	return NULL;
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

void expand_exit(t_minishell *mshell, char **line)
{
    char 	*e_pos;
	char	*new_line;
	char	*temp;
	char	*exit;
		
	e_pos = get_position(*line);
	if (e_pos && *(e_pos + 1) == '?')
	{
		exit = ft_itoa(mshell->e_code);
        temp = ft_strjoin((ft_substr(*line, 0, e_pos - *line)), exit);
        new_line = ft_strjoin(temp, (e_pos + 2));
        free(temp);
        free(*line);
        *line = new_line;
		e_pos = get_position(*line);
    }
}

void expand_var(t_minishell *mshell, char **line)
{
    char *var_pos;
    char *key;
    char *value;
    int len;

    var_pos = get_position(*line);
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
        var_pos = get_position(*line);
    }
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    t_minishell mshell;
    init_struct(&mshell, envp);

	printf("$USER=%s\n", get_value(&mshell, "USER"));
	printf("$HOME=%s\n", get_value(&mshell, "HOME"));

    char *line = strdup("echo o $? usuário é $USER $? $HOME $?");
    mshell.e_code = 127;
    if (!line) {
        perror("Falha ao alocar memória para a linha");
        return EXIT_FAILURE;
    }
    printf("Linha original: %s\n", line);
    handle_expansions(&mshell, &line);
    printf("Linha expandida: %s\n", line);
    free(line);
    return EXIT_SUCCESS;
}
