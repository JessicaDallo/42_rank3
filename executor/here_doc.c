/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:07:43 by sheila            #+#    #+#             */
/*   Updated: 2024/12/02 17:42:17 by shrodrig         ###   ########.fr       */
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
	char	*tmp_file;
	int		fd;
	static int		n;

	tmp_file = ft_strjoin("/tmp/heredoc_file",(ft_itoa(++n)));
	//printf("%s", tmp_file);
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if(!tmp_file)
	{
		error_msg("ERROR: ", "Failed to create temporary file");
		mshell->e_code = 1;
		return(-1);
	}
	return(fd);
}

void	here_doc(t_minishell *mshell, char *delim)
{
	int	pid;
	int	fd_here;
	char	*line;
	char	*end;
	
	end = (char *)malloc(sizeof(char) * (ft_strlen(delim) + 1));
	end = handle_quotes(delim, 0, 0);
	pid = (int)creat_pid(mshell);
	fd_here = tmp_heredoc(mshell);
	signal(SIGINT, SIG_IGN); // Ignorar SIGINT no processo principal
	signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT no processo principal
	if(pid == 0)
	{
		//printf("%s", end);
		signal(SIGINT, ft_sigint);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				error_msg("warning: heredoc delimited by EOF. Wanted", delim);
				break ;
			}
			if (!ft_strcmp(line, end))
			{
				free(line);
				break ;
			}
			if(is_expand(delim))
				handle_expansions(mshell, &line, 0);
			ft_putendl_fd(line, fd_here);
			free(line);
		}
		close(fd_here);
	}
	waitpid(pid, &mshell->e_code, 0);
	mshell->e_code = WEXITSTATUS(mshell->e_code);
}

/*int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    init_struct(&mshell, envp);
	char		*delimiter = "END";

	//signal(SIGINT, SIG_IGN); // Ignorar SIGINT no processo principal
	//signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT no processo principal
	//while(1){
	printf("Iniciando o heredoc. Digite %s para finalizar:\n", delimiter);
	here_doc(&mshell, delimiter);
	printf("Heredoc concluído com código de saída: %d\n", mshell.e_code);
	//}return (0);
}*/