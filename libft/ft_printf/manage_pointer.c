/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:58:36 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:58:40 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

static void		pointer_to_array(int buf[], void *p)
{
	unsigned int	dig;
	int				*j;
	int				k;

	buf[0] = '0';
	buf[1] = 'x';
	dig = 1;
	while (++dig < 15)
		buf[dig] = '0';
	j = p;
	k = 13;
	while (j)
	{
		dig = (size_t)j % 0x10;
		if (dig < 10)
			buf[k] = '0' + dig;
		else
			buf[k] = 'a' + (dig - 10);
		j = (void*)(((size_t)j) >> 4);
		--k;
	}
}

static int		write_value(t_format fmt, int buf[], void *p)
{
	int				output_size;
	int				dig;

	output_size = 0;
	if (fmt.sign_plus == 1)
		output_size += write(1, "+", 1);
	if (fmt.sign_space == 1 && fmt.sign_plus != 1)
		output_size += write(1, " ", 1);
	output_size += write(1, &buf[0], 1);
	output_size += write(1, &buf[1], 1);
	dig = 2;
	output_size += (p == 0 && fmt.precision != 0) ? write(1, "0", 1) : 0;
	while (buf[dig] == '0' && p != 0)
		dig++;
	while (dig < 14 && p != 0)
		output_size += write(1, &buf[dig++], 1);
	return (output_size);
}

static int		get_current_size(int buf[])
{
	int		size;
	int		i;

	i = 2;
	size = 2;
	while (buf[i] == '0')
		i++;
	while (i < 14)
	{
		size++;
		i++;
	}
	return (size);
}

static int		write_padding(t_format fmt, int buf[], void *p)
{
	int output_size;
	int str_len;

	str_len = get_current_size(buf);
	str_len += (p == 0) ? 1 : 0;
	str_len += (fmt.sign_plus == 1 || fmt.sign_space == 1) ? 1 : 0;
	output_size = 0;
	while (output_size < fmt.width - str_len)
	{
		(fmt.sign_null == 1) ? (write(1, "0", 1)) :
		(write(1, " ", 1));
		output_size++;
	}
	return (output_size);
}

int				manage_pointer(t_format fmt, va_list *ap)
{
	void	*p;
	int		output_size;
	int		buf[15];

	output_size = 0;
	p = va_arg(*ap, void*);
	pointer_to_array(buf, p);
	if (fmt.sign_minus == 1)
	{
		output_size += write_value(fmt, buf, p);
		output_size += write_padding(fmt, buf, p);
	}
	if (fmt.sign_minus == 0)
	{
		output_size += write_padding(fmt, buf, p);
		output_size += write_value(fmt, buf, p);
	}
	return (output_size);
}
