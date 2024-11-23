/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_builtins.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:28 by sheila            #+#    #+#             */
/*   Updated: 2024/11/23 17:55:24 by sheila           ###   ########.fr       */
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
#include <fcntl.h>
#include <stdbool.h> 
#include <signal.h>
#include <wait.h>
#include <readline/readline.h>
#include <readline/history.h>

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
	char	*name;
	char	**value;
	struct s_token *next;
}	t_token;

//typedef	struct s_cmd
//{
//	char	*name;
//	char	**line;
//	char 	*path;
//	int		pipe[2];
	
//	struct s_cmd	*next;	
//}	t_cmd;

typedef	struct s_env
{
	char	*key;
	char 	*value;
	
	struct s_env	*next;	
}	t_env;

typedef	struct s_minishell
{
	t_env	*env;
	t_token	*token;
	
	char	**envp;
	int		e_code;
	int		env_size;
	pid_t	pid;
	
}	t_minishell;



/*------------------------------------- BUILTINS -------------------------------------*/
int		is_builtin(t_minishell *mshell, t_token *token);
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
void    handle_input(char c, char **output, int s_quote, int d_quote);
char    *handle_quotes(char *str, int s_quote, int d_quote);




/*------------------------------------- ERROR -------------------------------------*/
void	free_envlist(t_env *env);
void	free_array(char **str);
void	clear_mshell(t_minishell *mshell);
void	error_msg(char *cmd, char *str);
void	perror_msg(char *cmd, char *str);
void	close_fds(void);


/*------------------------------------- JESSICA -------------------------------------*/
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


#endif
