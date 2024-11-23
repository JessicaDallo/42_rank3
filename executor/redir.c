/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:11:06 by sheila            #+#    #+#             */
/*   Updated: 2024/11/14 15:32:15 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/include_builtins.h"

void	redir_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if(fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Erro ao redirecionar o arquivo");
		return;
	}
	close(fd);	
}

void	redir_output(char *file, char *redir)
{
	int	fd;
	
	if(!redir[1])
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Erro ao redirecionar o arquivo");
		return;
	}
	close(fd);	
}

void	redir_error(char *file, char *redir)
{
	int	fd;
	
	if(!redir[2])
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return;
	}
	if (dup2(fd, STDERR_FILENO) < 0)
	{
		perror("Erro ao redirecionar o arquivo");
		return;
	}
	close(fd);	
}


void	handle_redir(char *file, char *redir)
{
	//falta tratar das expansoes de variaveis e tilde
	if(!ft_strcmp(redir, "<"))
		redir_input(file);
	else if(!ft_strcmp(redir, ">"))
		redir_output(file, redir);	
	else if(!ft_strcmp(redir, ">>"))
		redir_output(file, redir);
	else if(!ft_strcmp(redir, "2>"))
		redir_error(file, redir);
	else if(!ft_strcmp(redir, "2>>"))
		redir_error(file, redir);
}

