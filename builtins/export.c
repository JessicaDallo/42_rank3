/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:16:30 by sheila            #+#    #+#             */
/*   Updated: 2024/12/06 19:11:31 by shrodrig         ###   ########.fr       */
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

void    update_env(t_minishell *mshell, char *key, char *value)
{
    t_env   *temp;

    temp = mshell->env;
	while (temp != NULL)
    {
        if (ft_strcmp(temp->key, key) == 0)
        {
			free(temp->value);
            if(value)
	            temp->value = ft_strdup(value);
            else
                temp->value = ft_strdup("");
            break;
		}
        temp = temp->next;
	}
    if(!temp)
        add_env(mshell, key, value);
    return;
}

// void ft_export(t_minishell *mshell, char **line)
// {
// 	char	**new_env;
//     //t_env   *export;

//     if(!line || !line[0])
//         print_export(mshell);
//     else
//     {
//         while(*line)
//         {
//             if (!*line)
//                 return;
//             new_env = ft_split(*line, '=');
// 	        if(!new_env)
// 	    	    return;
//             update_env(mshell, new_env[0], new_env[1]);
//             free(new_env[0]);
//             free(new_env[1]);
//             free(new_env);
//             line++;
//         }
//     }
// }

void ft_export(t_minishell *mshell, t_token *tokens)
{
	char	**new_env;
    bool    flag;
    t_token   *temp;

    temp = temp->next;
    if(!temp || !temp->input)
        print_export(mshell);
    else
    {
        while(temp)
        {
            flag = true;
            if (!strchar(temp->input, '='))
                flag = false;
            new_env = ft_split(temp->input, '=');
	        if(!new_env)
	    	    return;
            update_env(mshell, new_env[0], new_env[1], flag);
            free_arrays(new_env);
            temp = temp->next;
        }
    }
}

/*int main(int argc, char **argv, char **envp)
{
    t_minishell    mshell;

    init_struct(&mshell, envp);
    (void)argc;
    (void)argv;
        ft_export(&mshell, NULL);
    return 0;
}*/

//int main(int argc, char **argv, char **envp)
//{
//    t_minishell    mshell;
    //t_env   *temp;

    //init_struct(&mshell, envp);
    
    //printf("\n--- Antes do export ---\n");
    
    //temp = mshell.env;
    //while (temp)
    //{
    //    printf("%s = %s\n", temp->key, temp->value);
    //    temp = temp->next;
    //}
    //printf("\nSIZE_ENV = %d\n", mshell.env_size);
    
    //if(argc > 1)
    //    ft_export(&mshell, argv++);
    
//    printf("\n--- Após o export ---\n");

//    temp = mshell.env;
//    while (temp)
//    {
//       printf("%s = %s\n", temp->key, temp->value);
//       temp = temp->next;
//    }
//    printf("\nSIZE_ENV = %d\n", mshell.env_size);
//    return 0;
//}