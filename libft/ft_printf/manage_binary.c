/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:57:33 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:57:35 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

static int			write_prefix(t_format fmt)
{
	int output_size;

	output_size = 0;
	if (fmt.sign_hash == 1)
		output_size += write(1, "b", 1);
	return (output_size);
}

static int			write_value(t_format fmt, char *string)
{
	int output_size;
	int str_len;

	output_size = 0;
	str_len = ft_strlen(string);
	if (str_len == 1 && string[0] == '0' && fmt.precision == 0)
		return (0);
	while (str_len++ < fmt.precision)
		output_size += write(1, "0", 1);
	output_size += write(1, string, ft_strlen(string));
	return (output_size);
}

static int			write_padding(t_format fmt, char *string)
{
	int output_size;
	int str_len;

	str_len = (fmt.sign_hash == 1) ?
			(ft_strlen(string) + 1) : ft_strlen(string);
	str_len = (fmt.precision > str_len) ? fmt.precision : str_len;
	output_size = 0;
	while (output_size < fmt.width - str_len)
	{
		(fmt.sign_null == 1) ?
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
			output_size += write_prefix(fmt);
		output_size += write_padding(fmt, string);
		if (fmt.sign_null == 0)
			output_size += write_prefix(fmt);
		output_size += write_value(fmt, string);
	}
	else
	{
		output_size += write_prefix(fmt);
		output_size += write_value(fmt, string);
		output_size += write_padding(fmt, string);
	}
	free(string);
	return (output_size);
}

int					manage_binary(t_format fmt, va_list *ap)
{
	unsigned	num;
	char		*string;

	num = va_arg(*ap, unsigned);
	string = ft_itoa_base_unsigned(num, 2);
	return (actual_output(fmt, string));
}
