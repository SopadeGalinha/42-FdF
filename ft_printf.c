/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:33:10 by jhogonca          #+#    #+#             */
/*   Updated: 2023/06/18 00:00:03 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_putchar(int fd, const char c, t_data *st)
{
	st->count += write(fd, &c, 1);
}

static void	ft_putstr(int fd, const char *str, t_data *st)
{
	if (!str)
		return (ft_putstr(fd, "(null)", st));
	while (*str)
		ft_putchar(fd, *str++, st);
}

static void	ft_hex_base(int fd, unsigned long nb, int fmt, t_data *st)
{
	char	*base;

	if (fmt == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (fmt == 'b')
		st->hex_ref = 2;
	if (fmt == 'o')
		st->hex_ref = 8;
	if (fmt == 'u')
		st->hex_ref = 10;
	if (nb >= st->hex_ref)
	{
		ft_hex_base(fd, nb / st->hex_ref, fmt, st);
		ft_hex_base(fd, nb % st->hex_ref, fmt, st);
	}
	else
		ft_putchar(fd, base[nb], st);
}

static void	flag_conversions(int fd, char fmt, t_data *st, va_list args)
{
	if (fmt == 'c')
		ft_putchar(fd, va_arg(args, int), st);
	if (fmt == 's')
		ft_putstr(fd, va_arg(args, char *), st);
	if (fmt == 'd' || fmt == 'i' || fmt == 'o' || fmt == 'b')
	{
		st->pointer = va_arg(args, int);
		if (st->pointer < 0)
		{
			ft_putchar(fd, '-', st);
			st->pointer *= -1;
		}
		ft_hex_base(fd, st->pointer, 'u', st);
	}
	if (fmt == 'x' || fmt == 'X' || fmt == 'u')
		ft_hex_base(fd, va_arg(args, unsigned int), fmt, st);
	if (fmt == 'p')
	{
		st->pointer = va_arg(args, long);
		if (st->pointer == 0)
			return (ft_putstr(fd, "(nil)", st));
		ft_putstr(fd, "0x", st);
		ft_hex_base(fd, st->pointer, 'x', st);
	}
}

int	ft_printf(int fd, const char *fmt, ...)
{
	t_data	st;
	va_list	args;

	st.count = 0;
	st.index = -1;
	va_start(args, fmt);
	while (fmt[++st.index])
	{
		st.hex_ref = 16;
		if (fmt[st.index] == '%')
		{
			if (fmt[++st.index] == '%')
				ft_putchar(fd, '%', &st);
			else
				flag_conversions(fd, fmt[+st.index], &st, args);
		}
		else
			ft_putchar(fd, fmt[st.index], &st);
	}
	va_end(args);
	return (st.count);
}
