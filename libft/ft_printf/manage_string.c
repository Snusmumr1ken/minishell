/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:58:50 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:58:52 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

static int			write_value(t_format fmt, char *string)
{
	int output_size;
	int str_len;

	output_size = 0;
	str_len = (fmt.precision != -1 && fmt.precision < ft_strlen(string)) ?
			(fmt.precision) : (ft_strlen(string));
	while (output_size < str_len)
	{
		write(1, &string[output_size], 1);
		output_size++;
	}
	return (output_size);
}

static int			write_padding(t_format fmt, char *string)
{
	int output_size;
	int str_len;

	str_len = (fmt.precision != -1 && fmt.precision < ft_strlen(string)) ?
			(fmt.precision) : (ft_strlen(string));
	output_size = 0;
	while (output_size < fmt.width - str_len)
	{
		(fmt.sign_null == 1) ? (write(1, "0", 1)) :
		(write(1, " ", 1));
		output_size++;
	}
	return (output_size);
}

int					manage_string(t_format fmt, va_list *ap)
{
	int		output_size;
	char	*string;

	output_size = 0;
	string = va_arg(*ap, char*);
	if (!string)
		return (write(1, "(null)", 6));
	if (fmt.sign_minus == 1)
	{
		output_size += write_value(fmt, string);
		output_size += write_padding(fmt, string);
	}
	if (fmt.sign_minus == 0)
	{
		output_size += write_padding(fmt, string);
		output_size += write_value(fmt, string);
	}
	return (output_size);
}
