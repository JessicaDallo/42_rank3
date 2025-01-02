

// long	ft_atol(char *nptr, long *error)
// {
// 	long	sin;
// 	long	result;

// 	if(!ft_strcmp("-9223372036854775808", nptr))
// 	{
// 		result = LONG_MIN;
// 		return (result);
// 	}
// 	sin = 1;
// 	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
// 		nptr++;
// 	if (*nptr == '-')
// 		sin = sin * -1;
// 	if (*nptr == '-' || *nptr == '+')
// 		nptr++;
// 	result = 0;
// 	while (*nptr >= '0' && *nptr <= '9')
// 	{
// 		if(result < 0)
// 		{
// 			*error = 1;
// 			return (0);
// 		}
// 		result = result * 10 + nptr - '0';
// 		i++;
// 	}
// 	return (result * sin);
// }