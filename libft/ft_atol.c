#include "libft.h"

long long	ft_atol(const char *nptr, int *error)
{
	long long	sin;
	long long	result;
	long		i;

	sin = 1;
	i = 0;
	result = 0;
	while (nptr[i] == 32 || (nptr [i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sin = sin * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
	//	printf("%lld\n", result);
		if(result < 0)
		{
		//	printf("entrou\n");
			*error = 1;
			return (0);
		}
		i++;
	}
	return (result * sin);
}
