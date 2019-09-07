/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:30:29 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:30:32 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void				initialize(void)
{
	int 			fd;
	extern char		**environ;
	int				i;

	if (!access(".minishellrc", F_OK))
		return ;
	fd = open(".minishellrc", O_WRONLY | O_CREAT);
	if (fd == -1)
		exit_with_error("minishellrc is not present, but it also cannot be created\0", data);
	fchmod(fd, 0755);
	i = -1;
	while (environ[++i])
	{
		write(fd, environ[i], ft_strlen(environ[i]));
		write(fd, "\n", 1);
	}
	close(fd);
}
