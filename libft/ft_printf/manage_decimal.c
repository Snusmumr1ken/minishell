/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:57:50 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:57:52 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

static int			write_prefix(t_format fmt, char *string)
{
	int output_size;

	output_size = 0;
	if (string[0] == '-')
		output_size += write(1, "-", 1);
	else if (fmt.sign_plus == 1)
		output_size += write(1, "+", 1);
	else if (fmt.sign_space == 1)
		output_size += write(1, " ", 1);
	return (output_size);
}

static int			write_value(t_format fmt, char *string)
{
	int output_size;
	int str_len;
	int i;

	output_size = 0;
	str_len = (string[0] == '-') ?
			(ft_strlen(string) - 1) : (ft_strlen(string));
	if (str_len == 1 && string[0] == '0' && fmt.precision == 0)
		return (0);
	while (str_len++ < fmt.precision)
		output_size += write(1, "0", 1);
	if (string[0] == '-')
	{
		i = 1;
		while (i < ft_strlen(string))
			output_size += write(1, &string[i++], 1);
	}
	else
		output_size += write(1, string, ft_strlen(string));
	return (output_size);
}

static int			write_padding(t_format fmt, char *string)
{
	int output_size;
	int str_len;

	str_len = (string[0] == '-') ? (ft_strlen(string) - 1) : ft_strlen(string);
	str_len = (fmt.precision > str_len) ? fmt.precision : str_len;
	str_len = (str_len == 1 && string[0] == '0' && fmt.precision == 0) ?
			0 : str_len;
	output_size = 0;
	if (string[0] == '-' || fmt.sign_plus == 1 || fmt.sign_space == 1)
		str_len++;
	while (output_size < fmt.width - str_len)
	{
		(fmt.sign_null == 1 && fmt.sign_minus == 0 &&
		((fmt.precision != -1 && fmt.precision < ft_strlen(string)) ||
		fmt.precision == -1)) ?
		(write(1, "0", 1)) : (write(1, " ", 1));
		output_size++;
	}
	return (output_size);
}

static int			actual_output(t_format fmt, char *string)
{
	int output_size;

	output_size = 0;
	if (fmt.sign_minus == 0)
	{
		if (fmt.sign_null == 1)
			output_size += write_prefix(fmt, string);
		output_size += write_padding(fmt, string);
		if (fmt.sign_null == 0)
			output_size += write_prefix(fmt, string);
		output_size += write_value(fmt, string);
	}
	else
	{
		output_size += write_prefix(fmt, string);
		output_size += write_value(fmt, string);
		output_size += write_padding(fmt, string);
	}
	free(string);
	return (output_size);
}

int					manage_decimal(t_format fmt, va_list *ap)
{
	long long	num;
	char		*string;

	if (fmt.len == hh)
		num = (char)(va_arg(*ap, int));
	else if (fmt.len == h)
		num = (short)va_arg(*ap, int);
	else if (fmt.len == ll || fmt.len == j || fmt.len == z)
		num = va_arg(*ap, long long);
	else if (fmt.len == l)
		num = va_arg(*ap, long);
	else
		num = va_arg(*ap, int);
	string = ft_itoa_base_signed(num, 10);
	return (actual_output(fmt, string));
}
