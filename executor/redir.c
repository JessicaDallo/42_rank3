/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Crd: 2024/11/03 22:11:06 by sheila            #+#    #+#             */
/*   Updated: 2024/12/04 17:42:31 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

bool	redir_input(char *filename)
{
	int		fd;
	char	*file;

	file = check_tilde(handle_quotes(filename, 0, 0));
	if (!file || !*file)
		file = handle_quotes(filename, 0, 0);
	if (access(file, F_OK) == 0 && access(file, R_OK) < 0)
	{
		error_msg(file, "Permission denied", 1);
		return false;
	}
	if(file[0] == '$')
	{
		error_msg(file, "Ambiguous redirect", 1);
		return(false);
	}
	fd = open(file, O_RDONLY);
	if(fd < 0)
	{
		error_msg(file, "", 1);
		return(false);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		error_msg("dup2","Error redirecting", 1);
		close(fd);
		return(false);
	}
	close(fd);
	return(true);
}


bool	redir_output(char *filename)
{
	int	fd;
	char	*file;

	file = check_tilde(handle_quotes(filename, 0, 0));
	if (!file)
		file = handle_quotes(filename, 0, 0);
	if (access(file, F_OK) == 0 && access(file, W_OK) < 0)
	{
		error_msg(file, "Permission denied", 1);
		return false;
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd < 0)
	{
		error_msg(file,"No such file or directory", 1);
		return(false);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror_msg("dup2","Error redirecting");
		close(fd);
		return(false);
	}
	close(fd);
	return(true);
}

bool	redir_append(char *filename)
{
	int	fd;
	char	*file;

	file = check_tilde(handle_quotes(filename, 0, 0));
	if (!file)
		file = handle_quotes(filename, 0, 0);
	if (access(file, F_OK) == 0 && access(file, W_OK) < 0)
	{
		error_msg(file, "Permission denied", 1);
		return false;
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd < 0)
	{
		error_msg(file,"No such file or directory", 1);
		return(false);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror_msg("dup2","Error redirecting");
		close(fd);	
		return(false);
	}
	close(fd);
	return(true);
}

void	remove_token(t_token **tokens, t_token **current)
{
	t_token	*tmp;
	t_token	*prev;

	if(!tokens || !*tokens || !current || !*current)
		return;
	tmp = *current;
	prev = NULL;
	if(tmp == *tokens)
		*tokens = tmp->next;
	else
	{
		prev = *tokens;
		while(prev && prev->next != tmp)
			prev = prev->next;
		if(prev)
			prev->next = tmp->next;
	}
	if(tmp->input)
		free(tmp->input);
	*current = tmp->next;
	free(tmp);
}

bool	handle_redir(t_token **tokens) //checar
{
	t_token	*temp;
	bool	flag;

	//printf("handle_redir_entrou\n");
	if (!tokens || !*tokens)
		return false;
	flag = true;
	temp = *tokens;
	while(temp)
	{	
		//printf("handle_redir_entrou no while\n");
		if(temp->type == INPUT_REDIR)
		{
			flag = redir_input(temp->input);
			remove_token(tokens, &temp);
		}
		else if(temp->type == OUTPUT_REDIR)
		{
			flag = redir_output(temp->input);
			remove_token(tokens, &temp);	
		}
		else if(temp->type == APPEND_REDIR)
		{
			flag = redir_append(temp->input);
			remove_token(tokens, &temp);
		}
		else
			temp = temp->next;
		if(!flag)
			break;
	}
	//printf("handle_redir_saiu\n");
	return(flag);
}
