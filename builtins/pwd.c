/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:20:19 by shrodrig          #+#    #+#             */
/*   Updated: 2024/10/22 13:57:29 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int ft_pwd(void)
{
    char pwd[PATH_MAX]; //tamanho maximo do caminho
    if (getcwd(pwd, sizeof(pwd)) != NULL)
        ft_putstr_fd(pwd, STDOUT_FILENO);
    else
		perror("pwd");//printar a mensaem de erro padrao. 
    return (1);
}

/*int main(void)
{
	ft_pwd();
	return (0);
}*/