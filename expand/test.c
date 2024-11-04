/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:37:06 by sheila            #+#    #+#             */
/*   Updated: 2024/11/04 15:48:42 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/*int main()
{

    char *temp;
    char *env_var = "$HOME";

    if (env_var[0] == '$')
        //temp = getenv(env_var + 1);
        temp = getenv("HOME");

    if (temp != NULL) {
        printf("Valor da variável de ambiente: %s\n", temp);
    } else {
        printf("Variável de ambiente não encontrada.\n");
    }

    return 0;
}*/

/*#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    char cwd[PATH_MAX];

    // Mudar o diretório para dois níveis acima
    if (chdir("42CC") == 0) {
        // Verificar o diretório atual
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Diretório atual: %s\n", cwd);
        } else {
            perror("Erro ao obter o diretório atual");
        }
    } else {
        perror("Erro ao mudar de diretório");
    }
    return 0;
}*/


//#include <stdio.h>
//#include <unistd.h>
//#include <string.h>
//#include <linux/limits.h>

//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	char			*newstr;
//	unsigned int	i;
//	unsigned int	j;

//	newstr = (char *)malloc(strlen(s1) + strlen(s2) + 1);
//	if (!newstr)
//		return (NULL);
//	i = 0;
//	while (s1[i])
//	{
//		newstr[i] = s1[i];
//		i++;
//	}
//	j = 0;
//	while (s2[j])
//	{
//		newstr[i + j] = s2[j];
//		j++;
//	}
//	newstr[i + j] = '\0';
//	return (newstr);
//}

//int main()
//{
//    char cwd[PATH_MAX];
//	char *path;
//	char *aux = '\0';
	
//	if (!aux || aux[0] == '~')
//	{
//		if ((strcmp(aux, "~") == 0))
//			path = getenv("HOME");
//		else
//			path = ft_strjoin((getenv("HOME")), (aux + 1));
//	}
//	else
//		path = "/home/sheila/Desktop";
//    if (chdir(path) == 0)
//	{    
//        if (getcwd(cwd, sizeof(cwd)) != NULL)
//		{
//            printf("Diretório atual: %s\n", cwd);
//        }
//		else
//		{
//            perror("Erro ao obter o diretório atual");
//        }
//    }
//	else
//	{
//        perror("Erro ao mudar de diretório");
//    }
//    return 0;
//}


//char	*ft_lsutils(char *argv)
//{
//	char	*suf;
//	char	*pref;
//	char	*find;
//	int 	i;

//	if(argv[0] == '*' && argv[1] == '.')
//		suf = (argv +2);
//	else
//	{
//		while(argv[i])
//		{
//			if(argv[i] == '[')
//				return;
//		}
//	}
//}
