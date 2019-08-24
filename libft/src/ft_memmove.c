/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:13:03 by anyvchyk          #+#    #+#             */
/*   Updated: 2018/10/26 13:30:12 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	char	*source;
	char	*destination;
	size_t	i;

	i = -1;
	source = (char*)src;
	destination = (char*)dest;
	if (source < destination)
	{
		while ((int)(--n) >= 0)
			destination[n] = source[n];
	}
	else
	{
		while (++i < n)
			destination[i] = source[i];
	}
	return (dest);
}
