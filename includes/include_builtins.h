/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_builtins.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:28 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 15:33:54 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//#include <linux/limits.h>
#include <fcntl.h>
#include <stdbool.h> 
#include <signal.h>
//#include <wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum
{
	CMD,       // Comando
	ARG,      // Argumentos  dos comandos
	OUTPUT_REDIR, // Redirecionamento de saida > subscreve o arquivo inteiro 
	APPEND_REDIR, // redirecionamento de saida >> adiciona no fim do arquivo 
	INPUT_REDIR,   // Redirecionamento entrada < adicioana inputs aparti de um arquivo 
	HEREDOC, //redirecionamento de entrada << fornece multiplas linhas de entrada no terminal, sem precisar de um arquivo 
} token_type;

typedef struct	s_token
{
	token_type type;
	char *input;
	struct s_token *next;
}	t_token;


typedef	struct s_cmd
{
	t_token *token;
	int		pipe[2];
	
	struct s_cmd	*next;	
}	t_cmd;


typedef	struct s_env
{
	char	*key;
	char 	*value;
	
	struct s_env	*next;	
}	t_env;

typedef	struct s_minishell
{
	t_env	*env;
	t_cmd	*cmd;
	
	char	**envp;
	int		e_code;
	int		env_size;
	pid_t	pid;
	
}	t_minishell;



/*------------------------------------- BUILTINS -------------------------------------*/
int		is_builtin(t_minishell *mshell, t_cmd *cmd);
int		ft_echo(t_minishell *mshell);
void    ft_env(t_env *env);
void	init_struct(t_minishell *mshell, char **envp);
void	init_env(t_minishell *mshell);
void    add_env(t_minishell *mshell, char *key, char *value);
void	ft_exit(t_minishell *mshell);
int		is_num(char *str);
int		get_exit(t_minishell *mshell);
int		ft_pwd(void);
void	ft_unset(t_minishell *mshell, char **line);
void    remove_env(t_minishell *mshell, char *key);
void	ft_export(t_minishell *mshell, char **line);
char    *get_value(t_minishell *mshell, char *key);
void	update_env(t_minishell *mshell, char *key, char *value);
void    ft_cd(t_minishell *mshell, char *args);
char	*go_path(char *env);



/*------------------------------------- EXPANSIONS -------------------------------------*/
void	handle_expansions(t_minishell *mshell, char **line);
char	*get_position(char *line);
char	*get_epos(char *line);
void	update_line(char **line, char *value, char *str);
void	expand_var(t_minishell *mshell, char **line);
void	expand_exit(t_minishell *mshell, char **line);



/*------------------------------------- ERROR -------------------------------------*/
void	free_envlist(t_env *env);
void	free_array(char **str);
void	clear_mshell(t_minishell *mshell);
void	error_msg(char *cmd, char *str);
void	perror_msg(char *cmd, char *str);
void	close_fds(void);

/*------------------------------------- SINTAX -------------------------------------*/
char    *handle_quotes(char *str, int s_quote, int d_quote);


/*------------------------------------- JESSICA -------------------------------------*/

/*------------------------------------ VALIDATE -------------------------------------*/
int		validate(char **arg);
int		val_sintax(char *arg);
bool	val_quot(char **arg);
bool	val_pipe(char **arg, int was_cmd);
bool	val_red(char **arg, int was_cmd);
bool	val_red_in(char **arg, int was_cmd);

/*------------------------------------ TOKENS -------------------------------------*/
//t_token	*add_token(t_token **token, char *arg,  token_type type);
t_token	*create_token(char *arg, token_type type);
void	*add_token(t_cmd **cmd, char *arg, token_type type, bool teste);
void	add_cmd(t_cmd **cmd);
void	parse_input(char *input);
void	get_tokens(char **cmd);
int		get_type(char *cmd, bool teste);
bool	is_delimiter(char *arg);
bool	check_quots(char *h_input);

void	ft_print_array(char **cmd);
void	ft_print_tokens(t_cmd **cmd);


void	quote_pointer(char **arg, char c);
// void	handle_value(char **arg, t_token **token, char *str);
int		ft_count_words(char *arg, char c);
int		quote_count(char *arg, char c);
// int		len_array(char **arg);
char	**find_cmd(char *arg, char **cmd);
bool	delimiter(char **arg);

void free_token_list(t_token *head);
void free_cmd(t_cmd *cmd);
void free_token(t_token *token);



#endif
