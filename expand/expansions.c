/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:06:49 by sheila            #+#    #+#             */
/*   Updated: 2024/11/03 19:15:26 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

//int	expand_vars(t_minishell *mshell, char *argv)
int	expand_vars(char *argv)
{
	char	*temp;
	
	temp = NULL;
	while(*argv)
	{
		if(*argv == '$')
		{
			if(ft_strcmp(argv, "$?") == 0)
				//return(mshell->e_code);
				return(ft_putstr_fd("111", STDOUT_FILENO), 1);
			else
			{
				temp = getenv(argv + 1); //ou usar a funçao *get_var
				if (temp)
					return(ft_putstr_fd(temp, STDOUT_FILENO), 1);
				else
					return(ft_putstr_fd("", STDOUT_FILENO), 1);
			}	
		}
		argv++;
	}
}

char *expand_tilde(char *argv)
{
	char	*temp;
		
	if (!argv || argv[0] == '~')
	{
		if ((strcmp(argv, "~") == 0))
			temp = go_path("HOME");
		else
			temp = ft_strjoin((go_path("HOME")), (argv + 1));
	}
	return(temp);
}

int	is_expand(char *argv)
{
	int	flag;

	flag = 0;
	while(*argv)
	{
		if(*argv == '\'')
			flag = 1;
		argv++;
	}
	return(flag);
}


//int main()
//{
//	expand_vars("$teste");
//    return 0;
//}