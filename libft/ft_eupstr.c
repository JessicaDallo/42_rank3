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

void	handle_space(char *str, char *temp)
{
	int	space;
	int	j;
	int	i;

	i = 0;
	j = 0;
	space = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			space = 1;
		if (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		{
			if (space == 1)
				temp[j++] = ' ';
			space = 0;
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
}

char	*eup_str(char *str)
{
	char	*temp;

	temp = NULL;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	handle_space(str, temp);
	return (temp);
}

// int main ()
// {
// 	char *av = "   jessica  ";
// 	printf("%s\n", eup_str(av));
// 	return (0);
// }
