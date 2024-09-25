

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

// void eup_str(char *str)
// {
// 	int i = 0;
// 	int space = 0;

// 	while(str[i] == ' ' || str[i] >= 9 && str[i] <= 13)
// 		i++;
// 	while(str[i] != '\0')
// 	{
// 		if (str[i] == ' ' || str[i] >= 9 && str[i] <= 13)
// 			space = 1;
// 		if (!(str[i] == ' ' )|| (str[i] >= 9 && str[i] <= 13))
// 		{
// 			if(space == 1)
// 				printf(" ");
// 			space = 0;
// 			write(1, &str[i], 1);
// 		}
// 		i++;
// 	}
// }

// char    *ft_strcpy(char *s1, char *s2)
// {
// 	int i = 0;
// 	while (s2[i] != '\0')
// 	{
// 		s1[i] = s2[i];
// 		i++;
// 	}
// 	s1[i] = '\0';
// 	free(s2);
// 	return (s1);
// }

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}


char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	str = calloc(ft_strlen(s) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char * eup_str(char *str)
{
	int i = 0;
	int j = 0;
	int space = 0;
	char *temp = NULL;

	temp = calloc(ft_strlen(str) , sizeof(char));
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

int main ()
{
	char *av = "   jes 	     sica  ";
    
	printf("%s\n", eup_str(av));
	return (0);
}

