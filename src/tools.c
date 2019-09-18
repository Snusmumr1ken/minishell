/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:56:17 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/11 10:56:19 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void				pwd(bool color)
{
	char			dir[1000];

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

void				env(char *p_to_rc)
{
	int				fd;
	char			*line;
	int				i;

	line = ft_strjoin(p_to_rc, "/.minishellrc");
	fd = open(line, O_RDONLY);
	free(line);
	line = NULL;
	while ((i = get_next_line(fd, &line)) == 1)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
}

static void			get_fd(int *fd, char *p_to_rc)
{
	char			*line;

	line = ft_strjoin(p_to_rc, "/.minishellrc");
	*fd = open(line, O_RDONLY);
	free(line);
	if (*fd == -1)
		exit_with_error("can't open rc file\0");
}

char				*get_line_from_rc(char *var, char *p_to_rc)
{
	int				fd;
	int				i;
	char			*line;
	char			*look_for;

	get_fd(&fd, p_to_rc);
	look_for = ft_strjoin(var, "=");
	while ((i = get_next_line(fd, &line)) == 1)
	{
		if (!ft_strncmp(look_for, line, ft_strlen(look_for)))
			break ;
		free(line);
		line = NULL;
	}
	free(look_for);
	close(fd);
	if (!ft_strlen(line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char				*cut_var(int num, char *line)
{
	char			*var;
	int				len;
	int				j;

	if (!line)
		return (NULL);
	len = ft_strlen(line) - (num - 1);
	var = (char*)malloc(len);
	var[len - 1] = '\0';
	j = 0;
	while (line[num])
	{
		var[j] = line[num];
		num++;
		j++;
	}
	return (var);
}
