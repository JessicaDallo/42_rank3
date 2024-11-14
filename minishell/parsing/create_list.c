#include "../include/minishell.h"

int	get_type(char *cmd )
{
	if(ft_strcmp (cmd, "|") == 0)
		return PIPE;
	else if(ft_strcmp(cmd, "<") == 0 || ft_strcmp(cmd, ">") == 0 || ft_strcmp(cmd, "<<") == 0 || ft_strcmp(cmd, ">>") == 0)
		return REDIR;
	else 
		return CMD;
}

t_token *create_token(char *arg)
{
	t_token *new_token;
	int type;

	new_token = calloc(1, sizeof(t_token));
	if(!new_token)
		return (NULL);
	type = get_type(arg);
	new_token->type = type;
	new_token->value = ft_strdup(arg);
	new_token->next = NULL;

	return (new_token);
}

void add_token(t_token **token, char *arg)
{
	t_token *temp;
	t_token *new_token;

	new_token = create_token(arg);
	if(!new_token)
		return ;
	if(token == NULL)
	{
		*token = new_token;
		return ;
	}
	temp = *token;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = new_token;
}

// void free_token(t_token *token)
// {
// 	t_token *temp;

// 	if(!token)
// 		return ;
// 	while(temp)
// 	{
// 		temp = head;
// 		head = head->next;
// 		free(temp->value);
// 		free(temp);
// 	}
// }