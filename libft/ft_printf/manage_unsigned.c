/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:59:03 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:59:05 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

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

	str_len = (ft_strlen(string) < fmt.precision) ?
			(fmt.precision) : (ft_strlen(string));
	str_len = (fmt.sign_plus == 1 || fmt.sign_space == 1) ?
			(str_len + 1) : (str_len);
	output_size = 0;
	while (output_size < fmt.width - str_len)
	{
		(fmt.sign_null == 1) ? (write(1, "0", 1)) :
		(write(1, " ", 1));
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
		output_size += write_padding(fmt, string);
		output_size += write_value(fmt, string);
	}
	else
	{
		output_size += write_value(fmt, string);
		output_size += write_padding(fmt, string);
	}
	free(string);
	return (output_size);
}

int					manage_unsigned(t_format fmt, va_list *ap)
{
	unsigned long long	num;
	char				*string;

	if (fmt.len == hh)
		num = (unsigned char)va_arg(*ap, unsigned);
	else if (fmt.len == h && fmt.type == 'U')
		num = va_arg(*ap, unsigned long);
	else if (fmt.len == h)
		num = (unsigned short)va_arg(*ap, unsigned);
	else if (fmt.len == ll || fmt.len == j || fmt.type == 'U')
		num = va_arg(*ap, unsigned long long);
	else if (fmt.len == l)
		num = va_arg(*ap, unsigned long);
	else
		num = va_arg(*ap, unsigned);
	string = ft_itoa_base_unsigned(num, 10);
	return (actual_output(fmt, string));
}
