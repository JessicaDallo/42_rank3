/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:10:05 by sheila            #+#    #+#             */
/*   Updated: 2024/12/29 14:22:08 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

 void	error_msg(char *cmd, char *str, int e_code) //alterar a funcao para incluir o exite code
 {
	t_minishell	**mshell;
	
	mshell = get_shell();
 	ft_putstr_fd("minishell: ", STDERR_FILENO);
 	ft_putstr_fd(cmd, STDERR_FILENO);
 	ft_putstr_fd(": ", STDERR_FILENO);
 	ft_putstr_fd(str, STDERR_FILENO);
 	ft_putstr_fd("\n", STDERR_FILENO);
	(*mshell)->e_code = e_code;
 }

 void	perror_msg(char *cmd, char *str)
 {
	t_minishell	**mshell;
	
	mshell = get_shell();
 	ft_putstr_fd("minishell: ", STDERR_FILENO);
 	ft_putstr_fd(cmd, STDERR_FILENO);
 	ft_putstr_fd(": ", STDERR_FILENO);
 	perror(str);
	(*mshell)->e_code = errno;
 }

// t_minishell	**get_shell(void)
// {
// 	static t_minishell	*mshell = NULL;
	
// 	return (&mshell);
// }

void	close_fds(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

