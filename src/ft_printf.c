/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarate <rzarate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 22:12:29 by rzarate           #+#    #+#             */
/*   Updated: 2018/03/19 22:16:01 by rzarate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	arg_handler(t_mst *args, va_list ap, int i, t_uni *d_type)
{
	if (args->id[i] == 'i' || args->id[i] == 'd' || args->id[i] == 'D' ||
			args->id[i] == 's' || args->id[i] == 'S' || args->id[i] == 'c' ||
			args->id[i] == 'C')
		d_type->imt = va_arg(ap, intmax_t);
	else if (args->id[i] == 'o' || args->id[i] == 'O' || args->id[i] == 'u' ||
			args->id[i] == 'U' || args->id[i] == 'x' || args->id[i] == 'X' ||
			args->id[i] == 'C' || args->id[i] == 'p')
		d_type->uimt = va_arg(ap, uintmax_t);
	if (args->id[i] == 'c' || args->id[i] == 'C')
		return (handle_c(args, i, d_type));
	else if (args->id[i] == 's' || args->id[i] == 'S')
		return (handle_s(args, i, d_type));
	else if (args->id[i] == 'i' || args->id[i] == 'd' || args->id[i] == 'D')
		return (handle_i(args, i, d_type));
	else if (args->id[i] == 'o')
		return (handle_o(args, i, d_type));
	else if (args->id[i] == 'u')
		return (handle_u(args, i, d_type));
	else if (args->id[i] == 'x' || args->id[i] == 'X')
		return (handle_x(args, i, d_type));
	else if (args->id[i] == '%' || args->id[i] == '%')
		return (handle_per(args, i));
	else if (args->id[i] == 'p')
		return (handle_p(d_type));
	return (0);
}

void	arg_scanner(char *fmt, t_mst *args, int n)
{
	size_t	i;
	int		x;
	int		i2;

	i = -1;
	i2 = 0;
	struct_initializer(args, n);
	while (++i < ft_strlen(fmt) - 1)
	{
		if (fmt[i] == '%')
		{
			x = i + 1;
			x += check_flags(fmt, x, args, i2);
			x += check_mfw(fmt, x, args, i2);
			if (fmt[x] == '.')
				x += check_precision(fmt, x, args, i2);
			x += check_mod(fmt, x, args, i2);
			args->id[i2] = check_ids(fmt[x]);
			args->n_chars[i2] = x - i;
			if (args->id[i2] == -1)
			{
				args->n_chars[i2]--;
				x--;
			}
			i += args->n_chars[i2];
			i2++;
		}
	}
}

static	int	printer(t_mst *args, va_list ap, char *fmt, t_uni *d_type)
{
	int i;
	int	i2;
	int c;

	c = 0;
	i2 = 0;
	i = -1;
	while (fmt[++i])
	{
		if (fmt[i] != '%')
		{
			ft_putchar(fmt[i]);
			c++;
		}
		else if (fmt[i] == '%')
		{
			c += arg_handler(args, ap, i2, d_type);
			i += args->n_chars[i2];
			i2++;
		}
	}
	return (c);
}

int			ft_printf(const char *fmt, ...)
{
	va_list	ap;
	t_mst	args;
	int		c_a;
	int		c;
	t_uni	d_type;

	c = 0;
	c_a = count_args((char *)fmt);
	if (!fmt)
		return (-1);
	if (c_a == 0)
	{
		ft_putstr(fmt);
		return (ft_strlen(fmt));
	}
	va_start(ap, fmt);
	arg_scanner((char *)fmt, &args, c_a);
	c = printer(&args, ap, (char *)fmt, &d_type);
	va_end(ap);
	struct_finalizer(&args);
	return (c);
}
