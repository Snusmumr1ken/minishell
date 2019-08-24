/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:58:10 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:58:12 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

static int			write_prefix(t_format fmt, char *string)
{
	int output_size;

	output_size = 0;
	if (fmt.sign_hash == 1 && string[0] != '0')
	{
		output_size += (fmt.type == 'x') ?
				write(1, "0x", 2) : write(1, "0X", 2);
	}
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
			(ft_strlen(string) + 2) : ft_strlen(string);
	str_len = (fmt.precision > str_len) ? fmt.precision : str_len;
	str_len = (ft_strlen(string) == 1 && string[0] == '0') ? 0 : str_len;
	output_size = 0;
	while (output_size < fmt.width - str_len)
	{
		(fmt.sign_null == 1 && fmt.sign_minus == 0) ?
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

int					manage_hex(t_format fmt, va_list *ap)
{
	unsigned long long	num;
	char				*string;
	int					i;

	if (fmt.len == hh)
		num = (unsigned char)va_arg(*ap, unsigned);
	else if (fmt.len == h)
		num = (unsigned short)va_arg(*ap, unsigned);
	else if (fmt.len == ll || fmt.len == j)
		num = va_arg(*ap, unsigned long long);
	else if (fmt.len == l)
		num = va_arg(*ap, unsigned long);
	else
		num = va_arg(*ap, unsigned);
	string = ft_itoa_base_unsigned(num, 16);
	if (fmt.type == 'x')
	{
		i = -1;
		while (++i < ft_strlen(string))
		{
			if (string[i] >= 'A' && string[i] <= 'Z')
				string[i] = string[i] + 32;
		}
	}
	return (actual_output(fmt, string));
}
