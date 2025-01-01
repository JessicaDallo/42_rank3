/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2025/01/01 23:31:48 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	tmp_heredoc(t_minishell *mshell)
{
	int	fd;
	
	fd = open("/tmp/heredoc_file0001", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if(fd < 0)
	{
		perror_msg("open","Erro ao abrir o arquivo");
		mshell->e_code = errno;
		return(-1);
	}
	return(fd);
}

void	read_heredoc(t_minishell *mshell, char *eof, bool expand)
{
	char	*line;
	int		fd;
	
	fd = tmp_heredoc(mshell);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			error_msg("warning: here-document delimited by EOF. Wanted", eof, 1);
			break ;
		}
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break;
		}
		if(expand)
			handle_expansions(mshell, &line, 1);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	exit(mshell->e_code);
}

void	ft_heredoc(t_minishell *mshell, char *delim)
{
	pid_t	pid;
	bool	expand;
	char	*eof;
	
	eof = handle_quotes(delim, 0, 0);
	expand = is_expand(delim);
	pid = creat_pid(mshell);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, ft_sigquit);
	if(pid == 0)
	{
		signal(SIGINT, ft_sigint_hd); 
		read_heredoc(mshell, eof, expand);
		exit(mshell->e_code);
	}
	waitpid(pid, &mshell->e_code, 0);
	check_exit_status(mshell);
}

void open_hd(t_minishell *mshell)
{
	int fd;

	fd = open("/tmp/heredoc_file0001", O_RDONLY);
	if (fd < 0)
	{
		perror_msg("open", "Erro ao abrir arquivo do heredoc");
		mshell->e_code = errno;
		return;
	}
	mshell->heredoc_fd = fd;
	unlink("/tmp/heredoc_file0001");
	return;
}

bool has_heredoc(t_minishell *mshell, t_token **tokens)
{
	t_token *temp;
	t_token *aux;
	bool    flag;

	temp = *tokens;
	flag = false;
	while (temp)
	{   
		aux = temp->next;
		if (temp->type == HEREDOC)
		{
			ft_heredoc(mshell, temp->input);
			open_hd(mshell);
			flag = true;
			remove_token(tokens, &temp);
		}
		temp = aux;
	}
	return (flag);
}

