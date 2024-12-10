/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:10:05 by sheila            #+#    #+#             */
/*   Updated: 2024/12/10 19:21:26 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

 void	error_msg(char *cmd, char *str)
 {
 	ft_putstr_fd("minishell: ", STDERR_FILENO);
 	ft_putstr_fd(cmd, STDERR_FILENO);
 	ft_putstr_fd(": ", STDERR_FILENO);
 	ft_putstr_fd(str, STDERR_FILENO);
 	ft_putstr_fd("\n", STDERR_FILENO);
 }

 void	perror_msg(char *cmd, char *str)
 {
 	ft_putstr_fd("minishell: ", STDERR_FILENO);
 	ft_putstr_fd(cmd, STDERR_FILENO);
 	ft_putstr_fd(": ", STDERR_FILENO);
 	perror(str);
	//mshell->e_code = errno;
 }

void	close_fds(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

