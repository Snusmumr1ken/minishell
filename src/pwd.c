/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:30:51 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:30:53 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(bool color)
{
	char dir[1000];

	if (getcwd(dir, 1000) == NULL)
		exit_with_error("getcwd failed in pwd function\0");
	if (color)
	{
		ft_printf("\033[34m");
		write(1, dir, ft_strlen(dir));
		ft_printf("\033[0m");
	}
	else
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
}	
