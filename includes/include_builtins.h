/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_builtins.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:28 by sheila            #+#    #+#             */
/*   Updated: 2024/12/04 18:08:14 by shrodrig         ###   ########.fr       */
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
	ARG,      // ARGumentos |
	OUTPUT_REDIR, // Redirecionamento de saida > subscreve o arquivo inteiro 
	APPEND_REDIR, // redirecionamento de saida >> adiciona no fim do arquivo 
	INPUT_REDIR,   // Redirecionamento entrada < adicioana inputs aparti de um arquivo 
	HEREDOC, //redirecionamento de entrada << fornece multiplas linhas de entrada no terminal, sem precisar de um arquivo 
} token_type;

typedef	struct s_var
{
	int		i;
	int		j;
	bool	is_val;
	char	*str;
	char	c;
	
}	t_var;

typedef struct	s_token
{
	token_type type;
	char	*input;
	
	struct s_token *next;
}	t_token;

typedef	struct s_cmd
{
	t_token	*tokens;
	int		fd[2];
	
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
	t_cmd	*commands;
	
	char	**envp;
	int		e_code;
	int		env_size;
	//pid_t	pid;
	
}	t_minishell;


/*------------------------------------- BUILTINS -------------------------------------*/
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
void    ft_env_reorder(char **keys, t_env *env);
void    print_export(t_minishell *mshell);
void	ft_env_sorted(char **keys, int len);
void    ft_cd(t_minishell *mshell, char *args);
char	*go_path(char *env);
int		is_builtin(t_minishell *mshell, t_cmd *commands);



/*------------------------------------- SYNTAX -------------------------------------*/
void		handle_expansions(t_minishell *mshell, char **line, int flag);
bool 		is_expand(char *delim);
char		*get_position(char *line, int flag);
char		*get_epos(char *line, int flag);
void		update_line(char **line, char *value, char *str);
void		expand_var(t_minishell *mshell, char **line, int flag);
void		expand_exit(t_minishell *mshell, char **line, int flag);
void		process_char(char current, char *result, t_var *aux);
char		*rm_space(char *str);
void		handle_input(char c, char **output);
char		*handle_quotes(char *str, int s_quote, int d_quote);
t_minishell	*get_shell(void);


/*------------------------------------- ERROR -------------------------------------*/
void		free_envlist(t_env *env);
void		free_array(char **str);
void		clear_mshell(t_minishell *mshell);
void		error_msg(char *cmd, char *str);
void		perror_msg(char *cmd, char *str);
void		close_fds(void);


/*------------------------------------- SIGNAL -------------------------------------*/
void		ft_sigint(int signal);
void		handle_signal(void);
void		ft_reset_prompt(int signal);
void		ft_sigquit(int signal);

/*------------------------------------- EXEC -------------------------------------*/
void		here_doc(t_minishell *mshell, char *delim);
int			tmp_heredoc(t_minishell *mshell);
pid_t		creat_pid(t_minishell *mshell);

int			check_execpath(t_minishell *mshell, char *path);
char		*get_execpath(t_cmd *token);
void		run_execve(t_minishell *mshell, t_cmd *token);

// void	exec_cmd(t_minishell *mshell, t_cmd *token);
// void 	handle_pipes(t_minishell *mshell, t_cmd *cmd);
// void	run_commands(t_minishell *mshell);


/*------------------------------------- REDIR -------------------------------------*/
void	handle_redir(t_token *tokens);
void    remove_redir(t_token *tokens);
void	redir_append(char *file);
void	redir_output(char *file);
void	redir_input(char *file);



t_token *cr_token(token_type type, const char *input);
t_token *cr_sample_tokens();




/*------------------------------------- JESSICA -------------------------------------*/
/*------------------------------------ VALIDATE -------------------------------------*/
int		validate(char **arg);
int		val_sintax(char *arg);
bool	val_quot(char **arg);
bool	val_pipe(char **arg, int was_cmd);
bool	val_red(char **arg, int was_cmd);
bool	val_red_in(char **arg, int was_cmd);

/*------------------------------------ TOKENS -------------------------------------*/
void	get_tokens(char *arg, t_minishell *mshell);
void	quote_pointer(char **arg, char c);
void	add_token(t_token **token, char *arg,  token_type type);
void	handle_value(char **arg, t_token **token);
int		ft_count_words(char *arg, char c);
int		quote_count(char *arg, char c);
int		get_type(char *cmd);
int		len_array(char **arg);
char	**find_cmd(char *arg, char **cmd);
bool	delimiter(char **arg);
bool	is_delimiter(char *arg);
t_token	*create_token(char *arg, token_type type);

//void	ft_print_tokens(t_token *token);
//void	ft_print_array(char **cmd);


#endif
