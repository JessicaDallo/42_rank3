/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:56:31 by shrodrig          #+#    #+#             */
/*   Updated: 2024/12/09 12:25:48 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"


void    remove_env(t_minishell *mshell, char *key)
{
    t_env   *temp;
    t_env   *aux;

    temp = mshell->env;
    aux = NULL;
    while(temp)
    {
        if(ft_strcmp(temp->key, key) == 0)
        {
            if (aux)
                aux->next = temp->next;
            else
                mshell->env = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            mshell->env_size--;
            return;
        }
        aux = temp; 
        temp = temp->next; 
        }
}

void ft_unset(t_minishell *mshell, t_token *tokens)
{
    t_token *temp;
    
    temp = tokens;
    temp = temp->next;
    while(temp)
    {
        if (!temp->input)
            return;
        remove_env(mshell, temp->input);
        temp = temp->next;
    }
}

//int	get_varname(char *key)
//{
//	while(*key)
//	{
//		if(!(ft_isalnum(key) || key == '_'))
//			return(1);
//		key++;
//	}
//	return(0);
//}

/*t_token *cr_token(token_type type, const char *input)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->input = strdup(input); // Copia o valor da string
    new_token->next = NULL;
    return new_token;
}

t_token *cr_sample_tokens()
{
    t_token *token1 = cr_token(CMD, "unset");
	t_token *token2 = cr_token(ARG, "ABC");
    t_token *token3 = cr_token(ARG, "CDE");
    t_token *token4 = cr_token(ARG, "FGH");
    //t_token *token5 = cr_token(ARG, "");
	//t_token *token6 = cr_token(ARG, "");

    // Conecte os tokens
    token1->next = token2;
    token2->next = token3;
	token3->next = token4;
    //token4->next = token5;
	//token5->next = token6;

    return token1; // Retorna o início da lista
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    init_struct(&mshell, envp);
    
    t_token *tokens = cr_sample_tokens();
    t_token *teste = cr_token(CMD, "export");

    printf(" ***** Antes de unset *****\n");
    ft_env(mshell.env);
    
    printf("\n ***** Apos unset *****\n");
    ft_unset(&mshell, tokens);
    ft_env(mshell.env);
    ft_export(&mshell, teste);
    clear_mshell(&mshell);
    free_tokens(tokens);
    free_tokens(teste);
    
    return 0;
}*/
