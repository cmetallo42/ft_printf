/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:03:21 by student           #+#    #+#             */
/*   Updated: 2020/09/04 13:03:27 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putunbr(unsigned int n, int *p)
{
	if (n > 9)
	{
		ft_putunbr((n / 10), p);
		ft_putunbr((n % 10), p);
	}
	else
	{
		*p = *p + 1;
		ft_putchar(n + '0');
	}
}

void	ft_putnbrf(int n, int *p)
{
	if (n < 0)
	{
		*p = *p + 1;
		ft_putchar('-');
		n = -n;
	}
	if (n == -2147483648)
	{
		ft_putchar('2');
		n %= 1000000000;
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbrf((n / 10), p);
		ft_putnbrf((n % 10), p);
	}
	else
	{
		*p = *p + 1;
		ft_putchar(n + '0');
	}
}


void	ft_putuhex(unsigned int n, int *p)
{
	if (n > 15)
	{
		ft_putuhex((n / 16), p);
		ft_putuhex((n % 16), p);
	}
	else if (n < 10)
	{
		*p = *p + 1;
		ft_putchar(n + '0');
	}
	else
	{
		*p = *p + 1;
		n == 10 ? ft_putchar('A') : 0;
		n == 11 ? ft_putchar('B') : 0;
		n == 12 ? ft_putchar('C') : 0;
		n == 13 ? ft_putchar('D') : 0;
		n == 14 ? ft_putchar('E') : 0;
		n == 15 ? ft_putchar('F') : 0;
	}
}

void	ft_puthex(unsigned int n, int *p)
{
	if (n > 15)
	{
		ft_puthex((n / 16), p);
		ft_puthex((n % 16), p);
	}
	else if (n < 10)
	{
		*p = *p + 1;
		ft_putchar(n + '0');
	}
	else
	{
		*p = *p + 1;
		n == 10 ? ft_putchar('a') : 0;
		n == 11 ? ft_putchar('b') : 0;
		n == 12 ? ft_putchar('c') : 0;
		n == 13 ? ft_putchar('d') : 0;
		n == 14 ? ft_putchar('e') : 0;
		n == 15 ? ft_putchar('f') : 0;
	}
}

void	flags_uhex(va_list args, int *p)
{
	unsigned int output;

	output = va_arg(args, unsigned int);
	ft_putuhex(output, p);
}

void	flags_hex(va_list args, int *p)
{
	unsigned int output;

	output = va_arg(args, unsigned int);
	ft_puthex(output, p);
}

void	flags_uint(va_list args, int *p)
{
	unsigned int output;

	output = va_arg(args, unsigned int);
	ft_putunbr(output, p);
}

void	flags_int(va_list args, int *p)
{
	int output;

	output = va_arg(args, int);
	ft_putnbrf(output, p);
}

void	ft_putadr(unsigned long n, int *p)
{
	if (n > 15)
	{
		ft_putadr((n / 16), p);
		ft_putadr((n % 16), p);
	}
	else if (n < 10)
	{
		*p = *p + 1;
		ft_putchar(n + '0');
	}
	else
	{
		*p = *p + 1;
		n == 10 ? ft_putchar('a') : 0;
		n == 11 ? ft_putchar('b') : 0;
		n == 12 ? ft_putchar('c') : 0;
		n == 13 ? ft_putchar('d') : 0;
		n == 14 ? ft_putchar('e') : 0;
		n == 15 ? ft_putchar('f') : 0;
	}
}

void	flags_adr(va_list args, int *p)
{
	void			*output;
	unsigned long	address;

	output = va_arg(args, void*);
	address = (unsigned long)(output);
	write(1, "0x", 2);
	*p = *p + 2;
	ft_putadr(address, p);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr_pf(char const *s, int *p)
{
	int i;

	i = -1;
	while (s[++i] != '\0')
	{
		ft_putchar(s[i]);
		*p = *p + 1;
	}
}

void	flags_str(va_list args, int *p)
{
	char *output;

	output = va_arg(args, char*);
	ft_putstr_pf(output, p);
}

void	parse_flags(int *i, const char *str, va_list args, int *p)
{
	*i = *i + 1;
    if (str[*i] == 'c')
        flags_str(args, p);
    if (str[*i] == 's')
        flags_str(args, p);
    if (str[*i] == 'p')
        flags_adr(args, p);
    if (str[*i] == 'd')
        flags_int(args, p);
    if (str[*i] == 'i')
        flags_int(args, p);
    if (str[*i] == 'u')
        flags_uint(args, p);
    if (str[*i] == 'x')
        flags_hex(args, p);
	if (str[*i] == 'X')
        flags_uhex(args, p);
	if (str[*i] == '%')
	{
		*p = *p + 1;
		write(1, "%", 1);
	}
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		p;

	i = -1;
	p = 0;
	va_start(args, format);
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
			flag_parser(&i, format, args, &p);
		else
			write(1, &format[i], 1);
	}
	va_end(args);
	return (p);
}

int main()
{
	char *str = "abcdefd";
	char c = 't';
	int i = 42;
	ft_printf("test1 %s %i %c test2", str, i, c);
	return(0);
}