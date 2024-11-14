#include "include/minishell.h"

int main ()
{
	char	*input = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if(*input)
			add_history(input);

		//printf("%s\n", input);
		
		validate(input);
		get_tokens(input);
		//get_tokens(input);
		//t_token **tokens = tokenize(const char *input)
	}
}