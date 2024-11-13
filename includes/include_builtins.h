/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_builtins.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:28 by sheila            #+#    #+#             */
/*   Updated: 2024/11/13 18:34:00 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

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


typedef	struct s_cmd
{
	char	*name;
	char 	*path;
	
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
	char	**line;
	int		e_code;
	int		env_size;
	pid_t	pid;
	
	struct s_minishell	*next;
}	t_minishell;



/*------------------------------------- BUILTINS -------------------------------------*/
int		is_builtin(t_minishell *mshell);
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




#endif
