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

char				*initialize(void)
{
	int 			fd;
	extern char		**environ;
	int				i;
	char 			dir[1000];

	getcwd(dir, 1000);
	if (!access(".minishellrc", F_OK))
		return (ft_strdup(dir));
	fd = open(".minishellrc", O_WRONLY | O_CREAT);
	if (fd == -1)
		exit_with_error("minishellrc is not present, but it also cannot be created\0");
	fchmod(fd, 0755);
	i = -1;
	while (environ[++i])
	{
		write(fd, environ[i], ft_strlen(environ[i]));
		write(fd, "\n", 1);
	}
	close(fd);
	return (ft_strdup(dir));
}
