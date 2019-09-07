/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_warranty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:29:56 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:29:57 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	tell_no_warranty(void)
{
	write(1, "Welcome to MINISHELL!\n\n", 23);
	write(1, "This minishell was created by anyvchyk.\n", 40);
	write(1, "And it goes with ABSOLUTELY NO WARRANTY.\n\n", 42);
}
