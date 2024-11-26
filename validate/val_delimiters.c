#include "../includes/include_builtins.h"

bool val_quot(char **arg)
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

bool val_pipe(char **arg, int was_cmd)
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

bool val_red(char **arg, int was_cmd)
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

bool val_red_in(char **arg, int was_cmd)
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
