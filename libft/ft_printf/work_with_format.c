/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:59:17 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:59:18 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

static t_format		set_default(void)
{
	t_format fmt;

	fmt.sign_minus = 0;
	fmt.sign_plus = 0;
	fmt.sign_null = 0;
	fmt.sign_hash = 0;
	fmt.sign_space = 0;
	fmt.width = -999;
	fmt.precision = -1;
	fmt.len = 0;
	fmt.type = ';';
	return (fmt);
}

static int			set_width_or_prec(const char *str, int pos, t_format *fmt,
																int w_or_p)
{
	int		num;

	num = 0;
	while (str[pos] >= 48 && str[pos] <= 57)
	{
		num = num * 10 + (str[pos] - 48);
		pos++;
	}
	(w_or_p == 1) ? (fmt->width = num) :
	(fmt->precision = num);
	return (pos);
}

static void			check_and_set_sign(char c, t_format *fmt, int *i)
{
	if (c == '0')
	{
		fmt->sign_null = 1;
		*i += 1;
	}
	if (c == '-')
	{
		fmt->sign_minus = 1;
		*i += 1;
	}
	if (c == '+')
	{
		fmt->sign_plus = 1;
		*i += 1;
	}
	if (c == '#')
	{
		fmt->sign_hash = 1;
		*i += 1;
	}
	if (c == ' ')
	{
		fmt->sign_space = 1;
		*i += 1;
	}
}

static void			check_all(const char *format, int *i,
		t_format *fmt, va_list *ap)
{
	if (format[*i] == '*')
	{
		fmt->width = va_arg(*ap, int);
		*i += 1;
	}
	check_and_set_sign(format[*i], fmt, i);
	check_and_set_len(format, i, fmt);
	if (format[*i] == '.' && format[*i + 1] == '*')
	{
		fmt->precision = va_arg(*ap, int);
		*i += 2;
	}
	if (format[*i] == '.')
		*i = set_width_or_prec(format, *i + 1, fmt, 2);
	if (format[*i] >= 49 && format[*i] <= 57)
		*i = set_width_or_prec(format, *i, fmt, 1);
}

int					set_format(const char *format, int i,
		t_format *fmt, va_list *ap)
{
	int prev;

	*fmt = set_default();
	prev = i;
	while (is_type(format[i]) == 0)
	{
		check_all(format, &i, fmt, ap);
		if (format[i] == '\0')
			break ;
		if (prev == i)
			i++;
		prev = i;
	}
	if (format[i] != '\0')
		fmt->type = format[i];
	return (++i);
}
