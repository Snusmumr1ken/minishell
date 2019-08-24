/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:58:00 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:58:01 by anyvchyk         ###   ########.fr       */
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

int					manage_float(t_format fmt, va_list *ap)
{
	int				output_size;
	long double		number;
	char			*string;

	fmt.precision = (fmt.precision == -1) ? (6) : (fmt.precision);
	number = (fmt.len == L) ? va_arg(*ap, long double) : va_arg(*ap, double);
	string = ftoa((long double)number, fmt.precision);
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
