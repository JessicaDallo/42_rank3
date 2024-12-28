/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_builtins.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:28 by sheila            #+#    #+#             */
/*   Updated: 2024/12/23 15:48:11 by sheila           ###   ########.fr       */
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
#include <linux/limits.h>
#include <limits.h>
#include <fcntl.h>
#include <stdbool.h> 
#include <signal.h>
#include <wait.h>
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


typedef struct s_split
{
	char	**arr;
	int		init;
	int		i;
	int		j;
	int		redir;
	int		rlen;
	int		cwords;
	int		total;
}	t_split;

typedef struct	s_token
{
	token_type	type;
	char		*input;
	
	struct s_token *next;
}	t_token;

typedef	struct s_cmd
{
	t_token	*tokens;
	int		fd[2];
	
	struct s_cmd *next;	
}	t_cmd;

typedef	struct s_env
{
	char	*key;
	char 	*value;
	bool	print;
	
	struct s_env	*next;	
}	t_env;

typedef	struct s_minishell
{
	t_env	*env;
	t_cmd	*commands;
	char	**envp;
	int		heredoc_fd;
	
	int		e_code;
	int		env_size;
	
}	t_minishell;

/*------------------------------------- BUILTINS -------------------------------------*/
int		ft_echo(t_minishell *mshell, t_token *tokens);

void    ft_env(t_env *env);
void    init_env(t_minishell *mshell);
void    add_env(t_minishell *mshell, char *key, char *value, bool flag);
void	init_struct(t_minishell *mshell, char **envp);

int		ft_exit(t_minishell *mshell, t_token *token);
int		get_exit(t_minishell *mshell, t_token *token);
int		is_num(char *str);

int		ft_pwd(void);

void	ft_unset(t_minishell *mshell, t_token *tokens);
void    remove_env(t_minishell *mshell, char *key);

void	ft_export(t_minishell *mshell, t_token *tokens);
void	update_env(t_minishell *mshell, char *key, char *value, bool flag);
char    *get_value(t_minishell *mshell, char *key);
void    print_export(t_minishell *mshell);
void    ft_env_reorder(char **keys, t_env *env);
void	ft_env_sorted(char **keys, int len);

void    ft_cd(t_minishell *mshell, t_token *token);
char	*go_path(char *env);
char    *check_tilde(char *input);

bool	is_builtin(t_cmd *commands);
void	run_builtin(t_minishell *mshell, t_cmd *commands);


/*------------------------------------- SYNTAX -------------------------------------*/
void	handle_expansions(t_minishell *mshell, char **line, int flag);
bool 	is_expand(char *delim);
char	*get_position(char *line, int flag);
char	*get_epos(char *line, int flag);
void	update_line(char **line, char *value, char *str);
void	expand_var(t_minishell *mshell, char **line, int flag);
void	expand_exit(t_minishell *mshell, char **line, int flag);

bool	process_char(char current, char *prev, char *result, bool *inside_quotes);
char	*rm_space(char *str);
char	*handle_quotes(char *str, int s_quote, int d_quote);

char	**convert_args(t_token *token);
int		ft_arraylen(t_token *token);


/*------------------------------------- ERROR -------------------------------------*/
t_minishell	*get_shell(void);
void		close_fds(void);
void		error_msg(char *cmd, char *str);
void		perror_msg(char *cmd, char *str);

void		free_array(char **str);
void		free_cmd(t_cmd *cmd);
void		free_envlist(t_env *env);
void		free_tokens(t_token *tokens);
void		clear_mshell(t_minishell *mshell);


/*------------------------------------- SIGNAL -------------------------------------*/
void	ft_sigint(int signal);
void	handle_signal(void);
void	ft_reset_prompt(int signal);
void	ft_sigquit(int signal);
void	ft_sigint_hd(int signal);


/*------------------------------------- EXEC -------------------------------------*/
void	ft_heredoc(t_minishell *mshell, char *delim);
int		tmp_heredoc(t_minishell *mshell);
void	read_heredoc(t_minishell *mshell, char *eof, bool expand);
void	open_hd(t_minishell *mshell);
bool	has_heredoc(t_minishell *mshell, t_token **tokens);

int		check_execpath(t_minishell *mshell, char *path);
int		execpath_error(t_minishell *mshell, char *path);
char	*get_execpath(char *cmd_name);
void	run_execve(t_minishell *mshell, t_token *token);

pid_t	creat_pid(t_minishell *mshell);
void	exec_cmd(t_minishell *mshell);
int		check_cmd(t_minishell *mshell, t_cmd **cmd, int *prev_fd);
void    run_cmd(t_minishell *mshell, t_cmd *cmd, int *prev_fd);

void	create_pipes(t_cmd *cmd);
void	close_pipes(t_cmd *cmd);
void	redir_fds(int redir, int local);


/*------------------------------------- REDIR -------------------------------------*/
void	handle_redir(t_token **tokens);
void	redir_append(char *filename);
void	redir_output(char *filename);
void	redir_input(char *filename);
void    remove_token(t_token **tokens, t_token **current);


/*------------------------------------- JESSICA -------------------------------------*/

/*------------------------------------ VALIDATE -------------------------------------*/
int		val_sintax(char *arg);
bool val_quot(char *arg, int *i);
bool val_pipe(char *arg, int *was_cmd, int *i);
bool val_red(char *arg, int *was_cmd, int *i);
bool val_red_in(char *arg, int *was_cmd, int *i);

/*------------------------------------ TOKENS -------------------------------------*/
t_token	*create_token(char *arg, token_type type);
t_cmd	*parse_input(char *input);
t_cmd	*get_tokens(t_cmd *cmd, char **h_input);
bool	is_delimiter(char *arg);
void	*add_token(t_cmd **cmd, char *arg, token_type type, bool new_cmd);
void	add_cmd(t_cmd **cmd);
int		get_type(char *cmd, bool new_cmd);
int		ft_count_words(char *s, char c);

char	**ft_split_quots(char *str, char c);
int		quote_count(char *arg, char c);
char	*ft_trim(char *str);
void	process_trim(t_split *spl);
int		is_redir(t_split *spl, char *str);
int		len_red(char *str, char c);

void	free_token_list(t_token *head);
void	free_cmd(t_cmd *cmd);
void	free_token(t_token *token);

void	ft_print_array(char **cmd);
void	ft_print_tokens(t_cmd **cmd);

#endif
