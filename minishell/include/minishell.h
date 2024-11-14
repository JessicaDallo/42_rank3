# ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum
{
	CMD,       // Comando
	PIPE,      // Pipe |
	REDIR,   // Redirecionamento >> << < >
} token_type;

typedef struct	s_token
{
	token_type type;
	char *value;
	struct s_token *next;
}	t_token;

//validate
void	validate(char *arg);


void	get_tokens(char *arg);
int	ft_count_words(char *arg, char c);
char	**find_cmd(char *arg, char **cmd);

t_token *create_token( char *arg);
void add_token(t_token **token, char *arg);
//void free_token(t_token *token);
int	get_type(char *cmd );


# endif