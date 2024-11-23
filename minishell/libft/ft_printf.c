/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrodrig <shrodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:06:45 by shrodrig          #+#    #+#             */
/*   Updated: 2024/05/15 14:38:31 by shrodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_printchar(va_arg(ap, int));
	else if (specifier == 's')
		count += ft_printstr(va_arg(ap, char *));
	else if (specifier == 'd')
		count += ft_printnbr((va_arg(ap, int)));
	else if (specifier == 'i')
		count += ft_printnbr((va_arg(ap, int)));
	else if (specifier == 'u')
		count += print_uint((va_arg(ap, unsigned int)));
	else if (specifier == 'p')
		count += ft_printptr(va_arg(ap, unsigned long long));
	else if (specifier == 'x')
		count += ft_printhex(va_arg(ap, unsigned int), 'x');
	else if (specifier == 'X')
		count += ft_printhex(va_arg(ap, unsigned int), 'X');
	else if (specifier == '%')
		count += ft_printperc();
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += print_format(*(++format), ap);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}

/*int	main(void)
{
	char	c = '@';
	int		n = 123456;
	int		x = -4321;
	unsigned int y = 42;
	ft_printf("%s\n", "Hello World"); 
	printf("%s\n", "Hello World");
	ft_printf("%c\n", c); 
	printf("%c\n", c);
	ft_printf("%d\n", n); 
	printf("%d\n", n);
	ft_printf("%i\n", x); 
	printf("%i\n", x);
	ft_printf("%u\n", y); 
	printf("%u\n", y);
	ft_printf("%p\n", &x); 
	printf("%p\n", &x);
	ft_printf("%X\n", y); 
	printf("%X\n", y);
	ft_printf("%x\n", y); 
	printf("%x\n", y);
}*/