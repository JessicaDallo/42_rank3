/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:09:28 by sheila            #+#    #+#             */
/*   Updated: 2024/12/31 12:20:01 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

/*bool	is_builtin(t_cmd *commands)
{
	if(!commands || !commands->tokens)
		return(false);
	else if (!(ft_strcmp(commands->tokens->input, "cd")))
		return(true);
	else if (!(ft_strcmp(commands->tokens->input, "echo")))
		return(true);
	 else if (!(ft_strcmp(commands->tokens->input, "env")))
	 	return(true);
	else if (!(ft_strcmp(commands->tokens->input, "exit")))
		return(true);
	else if (!(ft_strcmp(commands->tokens->input, "export")))
		return(true);
	else if (!(ft_strcmp(commands->tokens->input, "pwd")))
		return(true);
	else if (!(ft_strcmp(commands->tokens->input, "unset")))
		return(true);
	return(false);
}*/

bool	check_options(t_minishell *mshell, t_token *tokens)
{
	t_token   *temp;

    temp = tokens;
	if (!(ft_strcmp(temp->input, "unset")) || !(ft_strcmp(temp->input, "export")) \
		|| !(ft_strcmp(temp->input, "env")))
	{
		if(!temp->next)
			return (false);
		temp = temp->next;	
		if(ft_strncmp(temp->input, "-", 1) == 0)
        {
            mshell->e_code = 1;
            error_msg(tokens->input, "no support for options", 1);
            return (true);
        }
	}
	return (false);
}
void	run_builtin(t_minishell *mshell, t_cmd *commands)
{
	if(!commands || !commands->tokens)
		return;
	if(!check_options(mshell, commands->tokens))
	{
		if (!(ft_strcmp(commands->tokens->input, "cd")))
			ft_cd(mshell, commands->tokens);
		else if (!(ft_strcmp(commands->tokens->input, "echo")))
			ft_echo(mshell, commands->tokens);
		else if (!(ft_strcmp(commands->tokens->input, "env")))
	 		ft_env(mshell->env);
		else if (!(ft_strcmp(commands->tokens->input, "exit")))
			ft_exit(mshell, commands->tokens);
		else if (!(ft_strcmp(commands->tokens->input, "export")))
			ft_export(mshell, commands->tokens);
		else if (!(ft_strcmp(commands->tokens->input, "pwd")))
			ft_pwd(mshell, commands->tokens);
		else if (!(ft_strcmp(commands->tokens->input, "unset")))
			ft_unset(mshell, commands->tokens);
	}
	return;
}

int	is_builtin(t_minishell *mshell, t_cmd *commands)
{
	if(!commands || !commands->tokens)
		return(0);
	if(!check_options(mshell, commands->tokens))
	{
		if (!(ft_strcmp(commands->tokens->input, "cd")))
			return(ft_cd(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "echo")))
			return(ft_echo(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "env")))
			return(ft_env(mshell->env), 1);
		else if (!(ft_strcmp(commands->tokens->input, "exit")))
			return(ft_exit(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "export")))
			return(ft_export(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "pwd")))
			return(ft_pwd(mshell, commands->tokens), 1);
		else if (!(ft_strcmp(commands->tokens->input, "unset")))
			return(ft_unset(mshell, commands->tokens), 1);
	}
	return(0);
}


