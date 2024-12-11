/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2024/12/11 17:47:25 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

pid_t	creat_pid(t_minishell *mshell)
{
	pid_t	child;
	
	child = fork();
	if(child < 0)
	{
		perror_msg("ERROR", "fork");
		mshell->e_code = 127;
	}
	return(child);	
}

int	tmp_heredoc(t_minishell *mshell)
{
	int			fd;
	char		*tmp_file;
	char		*id;	
	static int	nbr;

	id = ft_itoa(++nbr);
	tmp_file = ft_strjoin("/tmp/heredoc_file", id);
	free(id);
	if(!tmp_file)
	{
		error_msg("ERROR: ", "Failed to create temporary file");
		mshell->e_code = 1;
		free(tmp_file);
		return(-1);
	}
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	free(tmp_file);
	if(fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		mshell->e_code = errno;
		return(-1);
	}
	return(fd);
}

void	read_heredoc(t_minishell *mshell, char *eof, int fd, bool expand)
{
	char	*line;
	
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			error_msg("warning: here-document delimited by EOF. Wanted", eof);
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
	if (dup2(fd, STDIN_FILENO) < 0)
		perror("Erro ao redirecionar o arquivo");
	close(fd);
	return;
}

void	ft_heredoc(t_minishell *mshell, char *delim)
{
	char	*eof;
	int		fd_here;
	bool	expand;
	pid_t	pid;
	
	//eof = (char *)calloc(ft_strlen(delim) + 1, sizeof(char));
	eof = handle_quotes(delim, 0, 0);
	pid = creat_pid(mshell);
	fd_here = tmp_heredoc(mshell);
	expand = is_expand(delim);
	signal(SIGINT, SIG_IGN); // Ignorar SIGINT no processo principal
	signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT no processo principal
	if(fd_here < 0)
		return;
	if(pid == 0)
	{
		signal(SIGINT, ft_sigint);
		read_heredoc(mshell,eof, fd_here, expand);
	}
	waitpid(pid, &mshell->e_code, 0);
	if(WIFEXITED(mshell->e_code)) // Verifica se o processo filho terminou normalmente (sem sinais)
		mshell->e_code = WEXITSTATUS(mshell->e_code); //extrai o código de saída (return code) do processo filho
	free(eof);
}

/*int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    init_struct(&mshell, envp);
	char	*delimiter = "END";
	char	*eof = handle_quotes(delimiter, 0, 0);

	printf("Iniciando o heredoc. Digite %s para finalizar:\n", eof);
	ft_heredoc(&mshell, delimiter);
	printf("Heredoc concluído com código de saída: %d\n", mshell.e_code);
	clear_mshell(&mshell);
	free(eof);
	return (0);
}*/
	