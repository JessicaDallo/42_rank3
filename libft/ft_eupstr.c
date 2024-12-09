/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eup_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:44:03 by sheila            #+#    #+#             */
/*   Updated: 2024/11/21 14:44:03 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*eup_str(char *str)
{
	int i = 0;
	int j = 0;
	int space = 0;
	char *temp = NULL;

	temp = ft_calloc(ft_strlen(str) , sizeof(char));
	if(!temp)
		return (NULL);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while(str[i] != '\0')
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			space = 1;
		if (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		{
			if(space == 1)
				temp[j++] = ' ';
			space = 0;
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

// int main ()
// {
// 	char *av = "   jessica  ";
    
// 	printf("%s\n", eup_str(av));
// 	return (0);
// }
