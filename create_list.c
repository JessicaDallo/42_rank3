#include "include/minishell.h"

t_token *create_token(token_type type, const char *value, int n)
{
	t_token *new_token;

	new_token = calloc(1, sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strndup(value, n);

	return (new_token);
}

void add_token(t_token **head, t_token *new_token)
{
	t_token *current;

	if(!*head)
		*head =  new_token;
	else
	{
		current = *head;
		while(current->next)
			current = current->next;
		current->next = new_token;
	}
}

void free_token(t_token *head)
{
	t_token *temp;

	while(head)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
}