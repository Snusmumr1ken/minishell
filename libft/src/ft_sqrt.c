/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 13:51:23 by anyvchyk          #+#    #+#             */
/*   Updated: 2018/10/22 14:03:46 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int check;

	check = 7;
	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	if (nb == 4)
		return (2);
	if (nb == 9)
		return (3);
	if (nb == 16)
		return (4);
	if (nb == 25)
		return (5);
	if (nb == 36)
		return (6);
	while (check < nb / 7)
	{
		if ((check * check) == nb)
			return (check);
		check++;
	}
	return (0);
}
