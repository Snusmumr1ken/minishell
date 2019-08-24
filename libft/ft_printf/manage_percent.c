/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:58:27 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:58:29 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libp.h"

int			manage_percent(t_format fmt)
{
	int		size_of_output;

	size_of_output = 1;
	if (fmt.sign_minus == 1)
		write(1, "%", 1);
	while (size_of_output < fmt.width)
	{
		(fmt.sign_null == 1) ? (write(1, "0", 1)) :
		(write(1, " ", 1));
		size_of_output++;
	}
	if (fmt.sign_minus == 0)
		write(1, "%", 1);
	return (size_of_output);
}
