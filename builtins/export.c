/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:16:30 by sheila            #+#    #+#             */
/*   Updated: 2024/12/09 11:45:08 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_builtins.h"

char    *get_value(t_minishell *mshell, char *key)
{
    t_env   *temp;

    temp = mshell->env;
	while (temp != NULL)
    {
        if (ft_strcmp(temp->key, key) == 0)
			return(temp->value);
        temp = temp->next;
    }
    return(NULL);
}

void    update_env(t_minishell *mshell, char *key, char *value, bool flag)
{
    t_env   *temp;

    temp = mshell->env;
	while (temp != NULL)
    {
        if (ft_strcmp(temp->key, key) == 0)
        {
            if (flag)
            {
                temp->print = true;
			    free(temp->value);
                if(value)
	                temp->value = ft_strdup(value);
                else
                    temp->value = ft_strdup("");
            }
            break;
		}
        temp = temp->next;
	}
    if(!temp)
        add_env(mshell, key, value, flag);
    return;
}


void ft_export(t_minishell *mshell, t_token *tokens)
{
	char	**new_env;
    bool    flag;
    t_token   *temp;

    temp = tokens;
    temp = temp->next;
    if(!temp || !temp->input)
        print_export(mshell);
    else
    {
        while(temp)
        {
            flag = true;
            if (!ft_strchr(temp->input, '='))
                flag = false;
            new_env = ft_split(temp->input, '=');
	        if(!new_env)
	    	    return;
            update_env(mshell, new_env[0], new_env[1], flag);
            free_array(new_env);
            temp = temp->next;
        }
    }
}

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
    t_token *token1 = cr_token(CMD, "export");
	t_token *token2 = cr_token(ARG, "ABC=123");
    t_token *token3 = cr_token(ARG, "CDE");
    t_token *token4 = cr_token(ARG, "FGH=456");
    t_token *token5 = cr_token(ARG, "ABC");
	t_token *token6 = cr_token(ARG, "FGH=789");

    // Conecte os tokens
    token1->next = token2;
    token2->next = token3;
	token3->next = token4;
    token4->next = token5;
	token5->next = token6;

    return token1; // Retorna o início da lista
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell mshell;
    
    init_struct(&mshell, envp);
    
    t_token *tokens = cr_sample_tokens();

    printf("\n ***** Antes de export *****\n");
    ft_env(mshell.env);
    ft_export(&mshell, tokens);
    
    printf("\n ***** Apos de export *****\n");
    t_token *teste = cr_token(CMD, "export");
    ft_env(mshell.env);
    ft_export(&mshell, teste);
    clear_mshell(&mshell);
    free_tokens(tokens);
    free_tokens(teste);
    
    return 0;
}*/
