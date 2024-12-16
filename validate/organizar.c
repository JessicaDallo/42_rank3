// ft_check_delimiters(char **arg, int *was_cmd)
// {
// 	if (*arg == '|')
// 		{
// 			if (!val_pipe(&arg, was_cmd) || !was_cmd)
// 				return (printf("ERROR pipe\n"));
// 		}
// 		if (*arg == '>')
// 		{
// 			if (!val_red(&arg, was_cmd))
// 				return (printf("ERROR redir\n"));
// 		}
// 		if (*arg == '<')
// 		{
// 			if (!val_red_in(&arg, was_cmd))
// 				return (printf("ERROR redir\n"));
// 		}
// 		if (*arg == '"' || *arg == '\'')
// 		{
// 			if (!val_quot(&arg))
// 				return (printf("ERROR quotation\n"));
// 		}
// }

// int	val_sintax(char *arg)
// {
// 	int	was_cmd;
// 	int i;

// 	i = 0;
// 	was_cmd = 0;
// 	while (*arg)
// 	{
// 		ft_check_delimiters(&arg, &was_cmd);
// 		if (*arg != ' ')
// 			was_cmd = 1;
// 		if (*arg != '\0')
// 			arg++;
// 		else
// 			break ;
// 	}
// 	return (0);
// }


// val_delimiters

// bool	val_quot(char **arg)
// {
// 	char	c;

// 	c = **arg;
// 	(*arg)++;
// 	while (**arg)
// 	{
// 		if (**arg == c && *(*arg - 1) != '\\')
// 		{
// 			(*arg)++;
// 			return (true);
// 		}
// 		(*arg)++;
// 	}
// 	return (false);
// }

// bool	val_pipe(char **arg, int was_cmd)
// {
// 	was_cmd = 0;
// 	(*arg)++;
// 	while (**arg)
// 	{
// 		if (**arg == '<' || **arg == '>' || **arg == '|')
// 			return (false);
// 		else if (**arg != ' ' && **arg != '|')
// 			was_cmd = 1;
// 		if (was_cmd == 1)
// 			return (true);
// 		(*arg)++;
// 	}
// 	return (was_cmd);
// }

// bool	val_red(char **arg, int was_cmd)
// {
// 	int	was_red;

// 	was_red = 1;
// 	(*arg)++;
// 	was_cmd = 0;
// 	while (**arg)
// 	{
// 		if (*(*arg + 1) == '>' && was_red)
// 			return (false);
// 		if ((**arg == '<' || **arg == '|') && !was_cmd)
// 			return (false);
// 		else if (**arg != ' ' && **arg != '>')
// 			was_cmd = 1;
// 		if (was_cmd == 1)
// 			return (true);
// 		(*arg)++;
// 	}
// 	return (was_cmd);
// }

// bool	val_red_in(char **arg, int was_cmd)
// {
// 	int	was_red;

// 	was_red = 1;
// 	(*arg)++;
// 	was_cmd = 0;
// 	while (**arg)
// 	{
// 		if (*(*arg + 1) == '<' && was_red)
// 			return (false);
// 		if ((**arg == '>' || **arg == '|') && !was_cmd)
// 			return (false);
// 		else if (**arg != ' ' && **arg != '<')
// 			was_cmd = 1;
// 		if (was_cmd == 1)
// 			return (true);
// 		(*arg)++;
// 	}
// 	return (was_cmd);
// }
