
static void	*ft_clear(char **str, size_t j)
{
	while (j--)
		free(str[j]);
	free(str);
	return (NULL);
}

// conta o numero de palavras da string
static int	ft_count_words(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

char	**ft_splitstr(char **str, char const *s, char c)
{
	int		j;
	int		i;

	j = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			if (!ft_strchr(s, c))
				i = ft_strlen(s);
			else
				i = ft_strchr(s, c) - s;
			str[j++] = ft_substr(s, 0, i);
			if (!str[j - 1])
				return (ft_clear(str, j - 1));
			s = s + i;
		}
		while (*s == c && *s)
			s++;
	}
	str[j] = NULL;
	return (str);
}

// cria uma string com a palavra, removendo o caractere c
char	**ft_split(char const *s, char c)
{
	char	**str;

	str = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!str)
		return (NULL);
	return (ft_splitstr(str, s, c));
}