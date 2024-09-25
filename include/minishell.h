# ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

typedef enum {
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

//create list
t_token *create_token(token_type type, char *value, int n);
void add_token(t_token **head, t_token *new_token);
void free_token(t_token *head);

//main

int main ();

//tokens
//token_type get_t_type(char* token);
void	get_tokens(char *arg);

//validate
void val_sintax(char *arg);

# endif