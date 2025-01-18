/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 08:41:51 by sheila            #+#    #+#             */
/*   Updated: 2025/01/04 19:27:28 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  
DEF: Allocates and returns an array of strings obtained by splitting 's'
using the character 'c' as a delimiter. The array must end with a NULL pointer.
RETURN VALUE: The array of new strings resulting from the split. NULL if
the allocation fails.  
*/

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (*str)
	{
		if (*str != c && i == 0)
		{
			i = 1;
			words++;
		}
		else if (*str == c)
			i = 0;
		str++;
	}
	return (words);
}

static char	*word_dup(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

/*
int main() {
    char str[] = "hello world, how are you?";
    char **words = ft_split(str, ' ');
    if (!words) {
        printf("Erro: não foi possível alocar memória.\n");
        return 1;
    }
    for (int i = 0; words[i] != NULL; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }
    free(words);
    return 0;
}*/