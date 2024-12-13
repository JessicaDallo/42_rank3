#include <stdio.h>

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

// int	ft_count_words(char *arg, char c)
// {
// 	int i;
// 	int was_cmd;

// 	i = 0;
// 	was_cmd = 0;
// 	while (*arg)
// 	{
// 		// while (*arg == c)
// 		// {
// 		// 	was_cmd = 0;
// 		// 	arg++;
// 		// }
// 		if(*arg == '"' || *arg == '\'')
// 		{
// 			quote_pointer(&arg, *arg);
// 			if(*arg == ' ' || *arg == '"' || *arg == '\'')
// 				i++;
// 			arg++;
// 		}
// 		else if (*arg != c && was_cmd == 0)
// 		{
// 			was_cmd = 1;
// 			i++;
// 		}
// 		else if (*arg == c)
// 			i++;
// 		// else if (*arg && !delimiter(&arg) && !was_cmd)
// 		// {
// 		// 	i++;
// 		// 	was_cmd = 1;
// 		// }
// 		// else if (delimiter(&arg))
// 		// {
// 		// //	if (*arg == '|')
// 		// 		i++;
// 		// 	was_cmd = 0;
// 		// }
// 		if (*arg == '\0')
// 			return i;
// 		arg++;
// 	}
// 	return (i);
// }


int ft_count_words(char *s, char c)
{
	int	i;
	char quots;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if(*s == '"' || *s == '\'')
		{
			quots = *s;
            s++;
			while(*s && *s != quots)
				s++;
			if (*s) 
                s++;
		}
		if (*s && *s != ' ')
        {
			i++;
        }
    	while (*s && *s != c  && *s != '"' && *s != '\'')
	    	s++;
	}
	return (i);
}

int main()
{
    int i;

    i = ft_count_words("echo teste 2 ' e | a | d'  ", '|');
    printf("%d\n", i);
}