/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2025/01/04 23:00:49 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tmp_heredoc()
{
	int	fd;

	fd = open("/tmp/heredoc_file0001", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror_msg("open", "Erro ao abrir o arquivo");
		g_e_code = errno;
		return (-1);
	}
	return (fd);
}

void	read_heredoc(t_minishell *mshell, char *eof, bool expand)
{
	char	*line;
	int		fd;

	fd = tmp_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			error_msg("warning:here-document delimited by EOF. Wanted", eof, 1);
			break ;
		}
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		if (expand)
			handle_expansions(mshell, &line, 1);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	free(eof);
	clear_mshell(mshell);
	//exit(mshell->e_code = 0);
}

void	ft_heredoc(t_minishell *mshell, char *delim)
{
	pid_t	pid;
	bool	expand;
	char	*eof;

	eof = handle_quotes(delim, 0, 0);
	expand = is_expand(delim);
	pid = creat_pid();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, ft_sigint_hd);
		read_heredoc(mshell, eof, expand);
		clear_mshell(mshell);
		//exit(mshell->e_code);
	}
	waitpid(pid, &g_e_code, 0);
	check_exit_status(mshell);
	free(eof);
	open_hd(mshell);
}

void	open_hd(t_minishell *mshell)
{
	int	fd;

	fd = open("/tmp/heredoc_file0001", O_RDONLY);
	if (fd < 0)
	{
		perror_msg("open", "Erro ao abrir arquivo do heredoc");
		g_e_code = errno;
		return ;
	}
	mshell->heredoc_fd = fd;
	close(fd);
	unlink("/tmp/heredoc_file0001");
	return ;
}

bool	has_heredoc(t_minishell *mshell, t_token **tokens)
{
	t_token	*temp;
	t_token	*aux;
	bool	flag;

	temp = *tokens;
	flag = false;
	while (temp)
	{
		aux = temp->next;
		if (temp->type == HEREDOC)
		{
			flag = true;
			ft_heredoc(mshell, temp->input);
			if (g_e_code == 130)
			{
				free_cmd(mshell->commands);
				mshell->commands = NULL;
				return (flag);
			}
			remove_token(tokens, &temp);
		}
		else
			temp = aux;
	}
	return (flag);
}
