
#include "../includes/include_builtins.h"

static int	split_delimiter(t_split *spl, char *str, char c)
{
	char *temp;

	if (str[spl->i] == c && spl->i > spl->init)
		{
			temp = ft_strndup(&str[spl->init], spl->i - spl->init);
			spl->arr[spl->j++] = temp;
			spl->init = spl->i + 1;
		}
		if ((size_t)spl->i < ft_strlen(str))
			spl->i++;
		else
			return (0);
	return (1);

}

static void	process_split(t_split *spl, char *str, char c)
{
	char	*temp;

	while (str[spl->i] != '\0')
	{
		if (str[spl->i] == '"' || str[spl->i] == '\'')
		{
			spl->i = spl->i + quote_count(&str[spl->i], str[spl->i]);
			if (str[spl->i] == c)
			{
				temp = ft_strndup(&str[spl->init], spl->i - spl->init);
				spl->arr[spl->j++] = temp;
				spl->init = spl->i + 1;
			}
		}
		else
		{
			if (!split_delimiter(spl, str, c))
				break ;
		}
	}
}

static void	process_split_red(t_split *spl, char *str, char c)
{
	char *temp;

	while(str[spl->i] != '\0')
	{
		spl->redir = is_redir(spl, str);
		if (str[spl->i] == '"' || str[spl->i] == '\'')
		{
			spl->i = spl->i + quote_count(&str[spl->i], str[spl->i]);
			if (str[spl->i] == c)
			{
				temp = ft_strndup(&str[spl->init], spl->i - spl->init);
				spl->arr[spl->j++] = temp;
				spl->init = spl->i + 1;
			}
		}
		else if(spl->redir)
		{
			if (spl->i > spl->init)
			{
				temp = ft_strndup(&str[spl->init], spl->i - spl->init);
				spl->arr[spl->j++] = temp;
			}
			temp = ft_strndup(&str[spl->i], spl->redir);
			spl->arr[spl->j++] = temp;
			spl->i += spl->redir;
			spl->init = spl->i;
		}
		else
			if(!split_delimiter(spl, str, c))
				break ;
	}

}
//debugar e ver o porque não está fazendo os splits comentei wait .h no include
char	**ft_split_quots(char *str, char c)
{
	t_split	spl;
	char	**arr;

	spl.i = 0;
	spl.j = 0;
	spl.init = spl.i;
	spl.arr = NULL;
	arr = ft_calloc(sizeof(char *), ft_count_words(str, c) + 1);
	if (!arr)
		return (NULL);
	spl.arr = arr;
	if(c == ' ')
		process_split_red(&spl, str, c);
	else
		process_split(&spl, str, c);
	if (spl.init < spl.i)
		spl.arr[spl.j++] = ft_strndup(&str[spl.init], spl.i - spl.init);
	spl.arr[spl.j] = NULL;
	process_trim(&spl);
	return (spl.arr);
}
