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

#include "../includes/minishell.h"

void	tell_no_warranty(void)
{
	write(1, "Welcome to MINISHELL!\n\n", 23);
	write(1, "This minishell was created by anyvchyk.\n", 40);
	write(1, "And it goes with ABSOLUTELY NO WARRANTY.\n\n", 42);
}

char				*initialize(void)
{
	int				fd;
	extern char		**environ;
	int				i;
	char			dir[1000];

	getcwd(dir, 1000);
	if (!access(".minishellrc", F_OK))
		return (ft_strdup(dir));
	fd = open(".minishellrc", O_WRONLY | O_CREAT);
	if (fd == -1)
		exit_with_error("minishellrc is not "
						"present, but it also cannot be created\0");
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
