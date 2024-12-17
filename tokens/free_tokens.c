#include "../includes/include_builtins.h"

//libera o que foi alocado  no inpute em seguida o nó 
void	free_token(t_token *token)
{
	if (token)
	{
		if (token->input)
			free(token->input);
		free(token);
	}
}

//lipera o token, e passa para o proximo 
void	free_token_list(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head->next;
		free_token(head);
		head = temp;
	}
}

// Libera a lista de tokens associada ao cmd, e em seguida o proprio cmd
void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd->next;
		if (cmd->token)
			free_token_list(cmd->token);
		free(cmd);
		cmd = temp;
	}
}
