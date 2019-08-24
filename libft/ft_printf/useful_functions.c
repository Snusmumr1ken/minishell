/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:59:10 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:59:12 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

int			is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' ||
		c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == 'f' ||
		c == '%' || c == 'b' || c == 'U')
		return (1);
	return (0);
}

int			ft_strlen(const char *str)
{
	int		size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}

int			what_to_manage(t_format fmt, va_list *ap)
{
	int output_size;

	if (fmt.type == 'c')
		output_size = manage_char(fmt, ap);
	if (fmt.type == 's')
		output_size = manage_string(fmt, ap);
	if (fmt.type == '%')
		output_size = manage_percent(fmt);
	if (fmt.type == 'p')
		output_size = manage_pointer(fmt, ap);
	if (fmt.type == 'd' || fmt.type == 'i')
		output_size = manage_decimal(fmt, ap);
	if (fmt.type == 'u' || fmt.type == 'U')
		output_size = manage_unsigned(fmt, ap);
	if (fmt.type == 'o')
		output_size = manage_octal(fmt, ap);
	if (fmt.type == 'b')
		output_size = manage_binary(fmt, ap);
	if (fmt.type == 'x' || fmt.type == 'X')
		output_size = manage_hex(fmt, ap);
	if (fmt.type == 'f' || fmt.type == 'F')
		output_size = manage_float(fmt, ap);
	return (output_size);
}

char		*ft_itoa_base_signed(long long value, int base)
{
	char				*s;
	unsigned long long	n;
	int					sign;
	int					i;

	n = (value < 0) ? -value : value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		i++;
	s = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	n = (value < 0) ? -value : value;
	while (i-- + sign)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base + 'A' - 10;
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}

char		*ft_itoa_base_unsigned(unsigned long long value,
										int base)
{
	char				*s;
	unsigned long long	n;
	int					i;

	n = value;
	i = 1;
	while ((n /= base) >= 1)
		i++;
	s = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	n = value;
	while (i--)
	{
		s[i] = (n % base < 10) ? (n % base + '0') : (n % base + 'A' - 10);
		n /= base;
	}
	return (s);
}
