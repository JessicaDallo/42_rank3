/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_builtins.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:28 by sheila            #+#    #+#             */
/*   Updated: 2024/10/24 20:08:16 by sheila           ###   ########.fr       */
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

typedef	struct s_env
{
	char	**keys;
	char 	**values;
	int		n_env;
	
	//struct s_env	*next;	
}	t_env;

typedef	struct s_minishell
{
	t_env	env;
	char	*cmd;
	char	**envp;
	char	**argv;
	int		e_code;
	
}	t_minishell;

int		ft_echo(t_minishell *mshell);
void	init_env(t_minishell *mshell);
void	init_struct(t_minishell *mshell, t_env *env, char **envp);
int		is_num(char *str);
int		ft_exit(t_minishell *mshell);
int		ft_pwd(void);
void	ft_unset(t_minishell *mshell, char *var);
void    get_value(t_minishell *mshell, char *value, int n);
void    get_newkey(t_minishell *mshell, char **temp);
void	ft_export(t_minishell *mshell, char **vars);
void	env_renew(t_minishell *mshell, char *key, char *value);
void    ft_cd(t_minishell *mshell, char *args);
char	*go_path(char *env);
void	perror_msg(char *cmd, char *str);




#endif
