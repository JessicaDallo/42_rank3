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
	OUTPUT_REDIR, // Redirecionamento de saida > subscreve o arquivo inteiro 
	APPEND_REDIR, // redirecionamento de saida >> adiciona no fim do arquivo 
	INPUT_REDIR,   // Redirecionamento entrada < adicioana inputs aparti de um arquivo 
	HEREDOC, //redirecionamento de entrada << fornece multiplas linhas de entrada no terminal, sem precisar de um arquivo 
} token_type;

typedef struct	s_token
{
	token_type type;
	char *value;
	struct s_token *next;
}	t_token;

//validate
int	validate(char **arg);

//tokens 
void	get_tokens(char *arg);
int	ft_count_words(char *arg, char c);
char	**find_cmd(char *arg, char **cmd);
void	quote_pointer(char **arg, char c);

int	quote_count(char *arg, char c);

bool delimiter(char **arg);

//create_list
t_token *create_token(char *arg,  token_type type);
void add_token(t_token **token, char *arg,  token_type type);
//void free_token(t_token *token);
int	get_type(char *cmd);

//ft_free
void	ft_free_array(char **cmd);
void	ft_free_token(t_token **token);


# endif