/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:16:30 by sheila            #+#    #+#             */
/*   Updated: 2024/12/03 17:30:21 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//{
//    char    **env;
//    char    **export;
//    t_var   *var;
    
//    var = malloc(sizeof(t_var));
//    var->i = 0;
//    env = NULL;
//    export = NULL;
//    while(*argv)
//    { 
//        if (!*argv)
//            return;
//        var->str = ft_split(*argv, ' ');
//	    if(!var->str)
//		    return;
//        if(ft_strchr(var->str, '=') == 0)
//            env[var->i++] = ft_strdup(var->str);
//        else
//            export[var->j] = ft_strdup(var->str);
//        free(var->str);
//        argv++;     
//    }
//    if(export)
//        add_exportlist();
//    return(env);
//}

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

void ft_export(t_minishell *mshell, char **line)
{
	char	**new_env;
    //t_env   *export;

    if(!line || !line[0])
        print_export(mshell);
    else
    {
        while(*line)
        {
            if (!*line)
                return;
            new_env = ft_split(*line, '=');
	        if(!new_env)
	    	    return;
            update_env(mshell, new_env[0], new_env[1]);
            free(new_env[0]);
            free(new_env[1]);
            free(new_env);
            line++;
        }
    }
}

void    ft_env_reorder(char **keys, t_env *env)
{
    int		i;
	t_env	*temp;

	i = -1;
	while (keys[++i])
	{
		temp = env;
		while (temp)
		{
			if (!ft_strcmp(keys[i], temp->key))
			{
				if (temp->value && ft_strlen(temp->value) > 0)
					ft_printf("declare -x %s=\"%s\"\n",temp->key, temp->value);
				else
					ft_printf("declare -x %s=\"\"\n", temp->key);
				break;
			}
			temp = temp->next;
		}
	}
}

void ft_env_sorted(char **keys, int len)
{
    char    *aux;
    int     i;
    int     j;

    j = 1;
	while (j < len)
	{
		i = 0;
		while (i < len)
		{
			if (ft_strcmp(keys[j], keys[i]) < 0)
			{
				aux = keys[j];
				keys[j] = keys[i];
				keys[i] = aux;
			}
			i++;
		}
		j++;
	}    
}

void    print_export(t_minishell *mshell)
{
    char	**keys;
	t_env	*temp;
	int		i;

	i = 0;
	temp = mshell->env;
	keys = ft_calloc(sizeof(char *), (mshell->env_size + 1));
	while (temp)
	{
		keys[i++] = ft_strdup(temp->key);
		temp = temp->next;
	}
	ft_env_sorted(keys, mshell->env_size);
    ft_env_reorder(keys, mshell->env);
    free_array(keys);
}


int main(int argc, char **argv, char **envp)
{
    t_minishell    mshell;

    init_struct(&mshell, envp);
    (void)argc;
    (void)argv;
        ft_export(&mshell, NULL);
    return 0;
}

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