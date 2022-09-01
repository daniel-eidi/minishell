/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:51:26 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/08/19 01:39:27 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_put_ph(const char **fmt, va_list ap, int *printrd_chars);

static char	*ft_itoa_base(unsigned int n, int len_base, char *base)
{
	unsigned int	len;
	char			*str;
	unsigned int	n_cpy;

	n_cpy = n;
	len = 0;
	if (n == 0)
		len = 1;
	while (n_cpy > 0)
	{
		n_cpy /= len_base;
		len ++;
	}
	str = (char *) malloc (len + 1);
	str[len] = '\0';
	if (n == 0)
		str[0] = base[0];
	while (n > 0)
	{
		str[--len] = base[n % len_base];
		n /= len_base;
	}
	return (str);
}

static char	*ft_itoa_address(void *n, int len_base, char *base)
{
	unsigned long	len;
	char			*str;
	unsigned long	n_cpy;

	n_cpy = (unsigned long) n;
	len = 0;
	len = ft_count_digit(n_cpy, len_base);
	len = len + 3;
	str = (char *) ft_calloc(1, len);
	str[--len] = '\0';
	if (n_cpy == 0)
		str[2] = base[0];
	while (n_cpy > 0)
	{
		str[--len] = base[n_cpy % len_base];
		n_cpy /= len_base;
	}
	str[1] = 'x';
	str[0] = '0';
	return (str);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		printrd_chars;

	printrd_chars = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			ft_put_ph(&fmt, ap, &printrd_chars);
			fmt++;
			continue ;
		}
		ft_putchar(*fmt);
		printrd_chars++;
		if (*fmt)
			fmt++;
	}
	va_end(ap);
	return (printrd_chars);
}

static int	ft_put_ph(const char **fmt, va_list ap, int *printrd_chars)
{
	if (**fmt == 'c')
		*printrd_chars += ft_putchar(va_arg(ap, int));
	else if (**fmt == 'd' || **fmt == 'i')
		*printrd_chars += ft_putnbr(va_arg(ap, int));
	else if (**fmt == 's')
		*printrd_chars += ft_putstr(va_arg(ap, char *), 0);
	else if (**fmt == 'u')
		*printrd_chars += ft_putstr(ft_itoa_base(va_arg(ap, int), 10, \
"0123456789"), 1);
	else if (**fmt == 'X')
		*printrd_chars += ft_putstr(ft_itoa_base(va_arg(ap, int), 16, \
"0123456789ABCDEF"), 1);
	else if (**fmt == 'x')
		*printrd_chars += ft_putstr(ft_itoa_base(va_arg(ap, int), 16, \
"0123456789abcdef"), 1);
	else if (**fmt == 'p')
		*printrd_chars += ft_putstr(ft_itoa_address(va_arg(ap, void *), \
16, "0123456789abcdef"), 1);
	else if (**fmt == '%')
		*printrd_chars += ft_putchar('%');
	return (*printrd_chars);
}
