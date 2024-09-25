#include "include/minishell.h"

int	val_syntax(char *arg)
{
	int	i;
	int	was_cmd;
	int	was_red;

	i = 0;
	was_cmd = 0;
	was_red = 0;
	while (arg[i])
	{
		if (arg[i] == '|')
		{
			if(!was_cmd)
			{
				return(printf("ERRO\n"));
			}
			was_cmd = 0;
			was_red = 0;
		}
		else if (arg[i] == '>')
		{
			if(arg[i+1] == '>' && was_red)
				return (printf("ERRO\n"), 1);
			was_cmd = 0;
			was_red++;
			if(was_red > 2)
				return (printf("ERRO\n"), 1);
		}
		else if (arg[i] == '<' || arg[i] == ' ')
		{
			if(arg[i+1] == '<' && was_red)
				return (printf("ERRO\n"), 1);
			was_cmd = 0;
			was_red++;
			if(was_red > 2)
				return (printf("ERRO\n"), 1);
		}
		else if (arg[i] != ' ' && arg[i] != '>' && arg[i] != '<')
		{
			was_cmd = 1;
			was_red = 0;
		}
		i++;
	}
	if (!was_cmd)
		return (printf("ERRO\n"), 1);
	return (0);
}

void val_sintax(char *arg)
{
	if(!*arg)
		return ;
	val_syntax(arg);
}



// int is_command(char *tokens)
// {
// 	if (ft_strcmp(tokens, "echo") == 0 || ft_strcmp(tokens, "cd") == 0)
// 		return (1);
// 	else if ((ft_strcmp(tokens, "pwd") == 0 || ft_strcmp(tokens, "export") == 0))
// 		return (1);
// 	else if ((ft_strcmp(tokens, "unset") == 0 || ft_strcmp(tokens, "env") == 0))
// 		return (1);
// 	else if (ft_strcmp(tokens, "exit") == 0 )
// 		return (1);
// 	else
// 		return (0);

		
// }
