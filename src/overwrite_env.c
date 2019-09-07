/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overwrite_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:30:45 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:30:47 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			write_all_without_old_var(char **tokens, int fd, int new_fd)
{
	char		*line;
	char		*temp;
	int 		res;

	while ((res = get_next_line(fd, &line)) == 1)
	{
		temp = ft_strjoin(tokens[1], "=");
		if (ft_strncmp(temp, line, ft_strlen(temp)))
		{
			write(new_fd, line, ft_strlen(line));
			write(new_fd, "\n", 1);
		}
		free(temp);
		free(line);
	}
	free(line);
}

void			overwrite(char **tokens)
{
	int 		fd;
	int 		new_fd;

	fd = open(".minishellrc", O_RDWR);
	new_fd = open(".tmp", O_RDWR | O_CREAT | O_APPEND);
	fchmod(new_fd, 0755);
	write_all_without_old_var(tokens, fd, new_fd);
	add_new_var(new_fd, tokens);
	remove(".minishellrc");
	rename(".tmp", ".minishellrc");
	close(fd);
	close(new_fd);
}
