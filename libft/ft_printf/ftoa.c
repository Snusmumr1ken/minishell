/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:57:09 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/02/08 11:18:52 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

static char			*strjoin(char *str1, char *str2)
{
	char		*result;
	int			i;
	int			j;

	result = (char*)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	result[ft_strlen(str1) + ft_strlen(str2)] = '\0';
	i = -1;
	while (str1[++i])
		result[i] = str1[i];
	j = -1;
	while (str2[++j])
	{
		result[i] = str2[j];
		i++;
	}
	return (result);
}

static void			round_double(long double *number, int precision)
{
	long double				rounder;
	unsigned long long		int_part;
	int						i;
	long double				temp;

	rounder = 0.1;
	i = 0;
	temp = (*number < 0) ? -*number : *number;
	int_part = (unsigned long long)temp;
	temp -= (long double)int_part;
	while (i <= precision)
	{
		temp *= 10;
		int_part = (unsigned long long)temp;
		temp -= (long double)int_part;
		i++;
	}
	while (precision--)
		rounder /= 10;
	if (int_part >= 5)
		*number = (*number < 0) ? (*number - rounder * 10) :
				(*number + rounder * 10);
}

static char			*get_after_dot(long double number, int precision)
{
	char					*result;
	unsigned long long		int_part;
	int						i;
	int						temp;

	result = (char*)malloc(precision + 1);
	result[precision] = '\0';
	int_part = (unsigned long long)number;
	number -= (long double)int_part;
	i = 0;
	while (i < precision)
	{
		number *= 10;
		temp = (int)number;
		result[i] = temp + 48;
		i++;
		number -= (long double)temp;
	}
	return (result);
}

char				*ftoa(long double number, int precision)
{
	char				*result;
	char				*before_dot;
	char				*after_dot;
	int					minus;

	precision = precision + 1 - 1;
	round_double(&number, precision);
	minus = (number < 0) ? 1 : 0;
	number = (number < 0) ? -number : number;
	before_dot = (minus) ?
		strjoin("-", ft_itoa_base_unsigned((unsigned long long)number, 10)) :
		ft_itoa_base_unsigned((unsigned long long)number, 10);
	if (precision == 0)
		return (before_dot);
	after_dot = strjoin(".", get_after_dot(number, precision));
	result = strjoin(before_dot, after_dot);
	free(before_dot);
	free(after_dot);
	return (result);
}
