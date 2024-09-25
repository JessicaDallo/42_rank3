#include "libft.h"

char	*ft_strndup(char *s, int n)
{
	char	*dest;
	int	len;

	len = ft_strnlen(s, n);
	if(n > ft_strlen(s))
	 	return (NULL);
	dest = (char *)malloc(len * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strncpy(dest, s, n);
	dest[len + 1] = '\0';
	return (dest);
}

// int main ()
// {
// 	char dst[] = "abcabcabc";
// 	printf ("%s deu?\n", ft_strndup(dst, 4, 6));
// 	printf("%s so dest\n", dst);
// 	return (0);
// }