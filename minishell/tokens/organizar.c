int	quote_count(char *arg, char c)
{
	int i;

	i= 0;
	i++;
	while (arg[i] != c)
	{
		i++;
	}
	i++;
	return (i);
}

bool	delimiter(char **arg)
{
	if (**arg == '|' || **arg == '>' || **arg == '<' || **arg == '\n')
	{
		if (*(*arg + 1 )== '<' || *(*arg) + 1 == '>')
			(*arg)++;
		return (true);
	}
	return (false);
}

void	quote_pointer(char **arg, char c)
{
	int i;
	
	i = 0;
	(*arg)++;
	while(**arg != c)
	{
		i++;
		(*arg)++;
	}
}