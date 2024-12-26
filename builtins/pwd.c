/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:20:19 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/23 15:39:44 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int ft_pwd(void)
{
    char pwd[PATH_MAX];
    if (getcwd(pwd, sizeof(pwd)) != NULL)
        ft_putstr_fd(pwd, STDOUT_FILENO);
    else
		  perror_msg("pwd", "pwd");
    ft_putstr_fd("\n", STDOUT_FILENO);
    return (0);
}
