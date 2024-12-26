/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2024/12/23 18:04:01 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

 void	create_pipes(t_cmd *cmd)
{
    t_cmd   *tmp;
    
    tmp = cmd;
    while (tmp)
    {
        if (tmp->next && pipe(tmp->fd) == -1)
        {
            perror_msg("pipe", "Erro ao criar pipe");
            return;
        }
        tmp = tmp->next;
    }
    return;
}

void    close_pipes(t_cmd *cmd)
{
    t_cmd   *tmp;
    
    tmp = cmd;
    while (tmp)
    {
        if (tmp->next && pipe(tmp->fd) == -1)
        {
            perror_msg("pipe", "Erro ao criar pipe");
            return;
        }
        tmp = tmp->next;
    }
}

void	redir_fds(int redir, int local)
{  
    if(redir < 0 || local < 0)
    {
        perror_msg("fd", "Erro ao abrir o arquivo");
        return;
    }
	else if (dup2(redir, local) < 0)
	{
		perror_msg("dup2", "Erro ao redirecionar o arquivo");
		return;
	}
    close(redir);
}


/*void	save_original_fds(int original_fds[2])
{
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
}

void	restore_original_fds(int original_fds[2])
{
	redirect_fd(original_fds[0], STDIN_FILENO);
	redirect_fd(original_fds[1], STDOUT_FILENO);
}*/
