/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_format2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 12:34:43 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/02/07 12:34:51 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

static void		check_and_set_len2(const char *str, int *i, t_format *fmt)
{
	if (str[*i] == 'l')
	{
		fmt->len = l;
		*i += 1;
	}
	if (str[*i] == 'L')
	{
		fmt->len = L;
		*i += 1;
	}
	if (str[*i] == 'z')
	{
		fmt->len = z;
		i += 1;
	}
}

void			check_and_set_len(const char *str,
		int *i, t_format *fmt)
{
	if (str[*i] == 'h' && str[*i + 1] == 'h')
	{
		fmt->len = hh;
		*i += 2;
	}
	if (str[*i] == 'l' && str[*i + 1] == 'l')
	{
		fmt->len = ll;
		*i += 2;
	}
	if (str[*i] == 'h')
	{
		fmt->len = h;
		*i += 1;
	}
	if (str[*i] == 'j')
	{
		fmt->len = j;
		*i += 1;
	}
	check_and_set_len2(str, i, fmt);
}
