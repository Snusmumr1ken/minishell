/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:57:18 by anyvchyk          #+#    #+#             */
/*   Updated: 2018/10/29 11:33:41 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s || (new = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	new = (char *)ft_memcpy(new, (s + start), len);
	new[len] = '\0';
	return (new);
}
