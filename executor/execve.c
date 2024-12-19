/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:06:12 by sheila            #+#    #+#             */
/*   Updated: 2024/12/17 22:29:18 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

int	execpath_error(t_minishell *mshell, char *path)
{
	if(ft_strchr(path, '/') || path[0] == '.')
	{
		if (access(path, F_OK) < 0)
		{
			error_msg(path, "No such file or directory");
			return(mshell->e_code = 127);
		}
		else if (access(path, X_OK) == 0)
		{
			error_msg(path, "Is a directory");
			return(mshell->e_code = 126);
		}
		else
		{
			error_msg(path, "Permission denied");
			return(mshell->e_code = 126);
		}
	}
	return(0);
}

int	check_execpath(t_minishell *mshell, char *path)
{
	if(!path || path == NULL)
	{
		error_msg(mshell->commands->tokens->input, "Command not found");
		return(mshell->e_code = 127);
	}
	else
		return(execpath_error(mshell, path));
	return(0);
}

char	*get_execpath(char *cmd_name)
{
	char	**paths;
	char	*tmp_path;
	int		i;
    char    *path;
	
	tmp_path = getenv("PATH");
	paths = ft_split(tmp_path, ':');
	if(!paths)
		return(NULL);
	i = -1;
	while(paths[++i])
	{
		path = ft_strjoin((ft_strjoin(paths[i], "/")), cmd_name);
		if(access(path, F_OK) == 0)
		{
			free_array(paths);
			return(ft_strdup(path));
		}
		free(path);
	}
	free_array(paths);
	return(NULL);
}

void	run_execve(t_minishell *mshell, t_token *token)
{
	char	*executable;
	char	**args;
	pid_t	pid;
	
	printf("\n ****** RUN EXECVE ******\n");
	pid = creat_pid(mshell);
	printf("PID criado: %d\n", pid);
	if(!token->input)
		return;
	args = convert_args(token);
	signal(SIGINT, SIG_IGN); // Ignorar SIGINT no processo principal
	signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT no processo principal
	if(pid == 0)
	{
		signal(SIGINT, ft_sigint);
		printf("Processo filho iniciado para EXECVE.\n");
		if(!args || !args[0])
			return;
		executable = get_execpath(args[0]);
		if(execve(executable, args, mshell->envp))
			check_execpath(mshell, executable);
		printf("Processo filho finalizado para EXECVE.\n");
		exit(mshell->e_code);
	}
	printf("Aguardando filho com waitpid EXECVE.\n");
	waitpid(pid, &mshell->e_code, 0);
	if(WIFEXITED(mshell->e_code)) // Verifica se o processo filho terminou normalmente (sem sinais)
		mshell->e_code = WEXITSTATUS(mshell->e_code); //extrai o código de saída (return code) do processo filho
	free_array(args);
	printf("Finalizando EXECVE.\n");
	return;
}

/*t_token *cr_token(token_type type, const char *input)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->input = strdup(input); // Copia o valor da string
    new_token->next = NULL;
    return new_token;
}

t_token *cr_sample_tokens()
{
    t_token *token1 = cr_token(CMD, "cat");
	t_token *token2 = cr_token(ARG, "Makefile");
    t_token *token3 = cr_token(ARG, "new.txt");
    t_token *token4 = cr_token(ARG, "<<END");
    //t_token *token5 = cr_token(ARG, "");
	//t_token *token6 = cr_token(ARG, "");

    // Conecte os tokens
    token1->next = token2;
    token2->next = token3;
	token3->next = token4;
    //token4->next = token5;
	//token5->next = token6;;

    return token1; // Retorna o início da lista
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    init_struct(&mshell, envp);
	mshell.commands = malloc(sizeof(t_cmd));
    if (!mshell.commands)
        return (1);
    ft_bzero(mshell.commands, sizeof(t_cmd));
	mshell.commands->tokens = cr_sample_tokens();
	run_execve(&mshell, mshell.commands->tokens);
	printf("\nEXIT CODE Main: %d\n", mshell.e_code);
	clear_mshell(&mshell);
    return 0;
}*/

/*void	wait_childs(t_minishell *mshell, t_cmd *cmd)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	while (cmd)
	{
		waitpid(mshell->pid, &status, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(status))
		mshell->e_code = WEXITSTATUS(status);
}*/
