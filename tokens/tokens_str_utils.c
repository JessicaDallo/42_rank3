#include "../includes/include_builtins.h"

//ideia
int	is_redir(t_split *spl, char *str)
{
	if(str[spl->i] == '<' || str[spl->i] == '>')
	{
		if (str[spl->i] == '<' && str[spl->i + 1] == '<')
			return (2);
		if (str[spl->i] == '>' && str[spl->i + 1] == '>')
			return (2);
		return (1);
	}
	return (0);
}

char	*ft_trim(char *str)
{
	int	j;
	int	i;
	int x;
	char *temp;

	i = 0;
	x = 0;
	j = ft_strlen(str) - 1;
	while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while(str[j] == ' ' || (str[j] >= 9 && str[j] <= 13))
		j--;
	temp = ft_calloc(sizeof(char), j - i);
	while(i <= j)
	{
		temp[x] = str[i];
		i++;
		x++;
	}
	temp[x] = '\0';
	return (temp);
}

void	process_trim(t_split *spl)
{
	int	i;

	i = 0;
	while(spl->arr[i] != NULL)
	{
		spl->arr[i] = ft_trim(spl->arr[i]);
		i++;
	}
}