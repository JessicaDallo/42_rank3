#include "../include/minishell.h"

static bool val_quot(char **arg)
{
	char c;

	c = **arg;
	(*arg)++;
	while (**arg)
	{
		if(**arg == c && *(*arg - 1) != '\\')
		{
			(*arg)++;
			return (true);
		}
		(*arg)++;
	}
	return (false);
}

static bool val_pipe(char **arg, int was_cmd)
{
	was_cmd = 0;
	(*arg)++;
	while(**arg)
	{
		if(**arg == '<' || **arg == '>' || **arg == '|')
			return (false);
		else if(**arg != ' ' && **arg != '|')
			was_cmd = 1;
		if(was_cmd == 1)
			return (true);
		(*arg)++;
	}
	return (was_cmd);
}

static bool val_red(char **arg, int was_cmd)
{
	int was_red;

	was_red = 1;
	(*arg)++;
	was_cmd = 0;
	while(**arg)
	{
		if (*(*arg + 1) == '>' && was_red)
			return (false);
		if((**arg == '<' || **arg == '|') && !was_cmd)
			return (false);
		else if (**arg != ' ' && **arg !='>')
			was_cmd = 1;
		if(was_cmd == 1)
			return (true);
		(*arg)++;
	}
	return (was_cmd);
}

static bool val_red_in(char **arg, int was_cmd)
{
	int was_red;

	was_red = 1;
	(*arg)++;
	was_cmd = 0;
	while(**arg)
	{
		if (*(*arg + 1) == '<' && was_red)
			return (false);
		if((**arg == '>' || **arg == '|') && !was_cmd)
			return (false);
		else if (**arg != ' ' && **arg !='<')
			was_cmd = 1;
		if(was_cmd == 1)
			return (true);
		(*arg)++;
	}
	return (was_cmd);
}

int	val_sintax(char *arg)
{
	int	was_cmd;

	was_cmd = 0;
	while (*arg)
	{
		if (*arg == '"' || *arg == '\'')
		{
			if(!val_quot(&arg))
				return (printf("ERROR quotation\n"));
		}
		else if (*arg == '|')
		{
			if(!val_pipe(&arg, was_cmd) || !was_cmd)
				return (printf("ERROR pipe\n"));
		}
		else if (*arg == '>')
		{
			if(!val_red(&arg, was_cmd))
				return (printf("ERROR redir\n"));
		}
		else if (*arg == '<')
		{
			if(!val_red_in(&arg, was_cmd))
				return (printf("ERROR redir\n"));
		}
		if(*arg != ' ')
			was_cmd = 1;
		arg++;
	}
	return (0);
}

void validate(char *input)
{
	if(!input)
		return ;
	input = eup_str(input);
	printf("%s\n", input);
	val_sintax(input);
}