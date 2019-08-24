/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:56:59 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:57:02 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_format	fmt;
	int			size_of_output;
	int			i;
	int			len_of_format;

	i = 0;
	size_of_output = 0;
	len_of_format = ft_strlen(format);
	va_start(ap, format);
	while (i < len_of_format)
	{
		if (format[i] == '%')
		{
			i = set_format(format, i + 1, &fmt, &ap);
			if (fmt.type != ';')
				size_of_output += what_to_manage(fmt, &ap);
			continue;
		}
		write(1, &format[i], 1);
		i++;
		size_of_output++;
	}
	return (size_of_output);
}
