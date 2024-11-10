/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_builtins.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:28 by sheila            #+#    #+#             */
/*   Updated: 2024/11/09 19:19:45 by sheila           ###   ########.fr       */
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
#include <limits.h>
#include <linux/limits.h>
#include <fcntl.h>
#include <stdbool.h> 

typedef	struct s_env
{
	char	*key;
	char 	*value;
	
	struct s_env	*next;	
}	t_env;

typedef	struct s_minishell
{
	t_env	*env;
	char	*cmd;
	char	**envp;
	char	**argv;
	int		e_code;
	int		env_size;
	
	struct s_minishell	*next;
}	t_minishell;



/*--------------------- BUILTINS ---------------------*/

int		is_builtin(t_minishell *mshell);
int		ft_echo(t_minishell *mshell);
void    ft_env(t_env *env);
void	init_struct(t_minishell *mshell, char **envp);
void	init_env(t_minishell *mshell);
void    add_env(t_minishell *mshell, char *key, char *value);
int		ft_exit(t_minishell *mshell);
int		is_num(char *str);
int		ft_pwd(void);
void	ft_unset(t_minishell *mshell, char **line);
void    remove_env(t_minishell *mshell, char *key);
void	ft_export(t_minishell *mshell, char **line);
char    *get_value(t_minishell *mshell, char *key);
void	update_env(t_minishell *mshell, char *key, char *value);
void    ft_cd(t_minishell *mshell, char *args);
char	*go_path(char *env);
void	perror_msg(char *cmd, char *str);

/*--------------------- EXPANSIONS ---------------------*/
void	handle_expansions(t_minishell *mshell, char **line);
char	*get_position(char *line);
//void	update_line(char **line, char *value, char *e_code, char *str);
void	update_line(char **line, char *value, char *str);
void	expand_var(t_minishell *mshell, char **line);
void	expand_exit(t_minishell *mshell, char **line);


#endif
