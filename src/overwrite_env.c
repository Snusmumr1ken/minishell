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

static void			write_all_without_old_var(char *var_name, int fd, int new_fd)
{
	char		*line;
	char		*temp;
	int 		res;

	temp = ft_strjoin(var_name, "=");
	while ((res = get_next_line(fd, &line)) == 1)
	{
		if (ft_strncmp(temp, line, ft_strlen(temp)))
		{
			write(new_fd, line, ft_strlen(line));
			write(new_fd, "\n", 1);
		}
		free(line);
	}
	free(line);
	free(temp);
}

void			overwrite(char *var_name, char *var_value, char *p_to_rc)
{
	int 		fd;
	int 		new_fd;
	char		*absolute_path_to_rc;
	char		*absolute_path_to_tmp;

	absolute_path_to_tmp = ft_strjoin(p_to_rc, "/.tmp");
	absolute_path_to_rc = ft_strjoin(p_to_rc, "/.minishellrc");
	fd = open(absolute_path_to_rc, O_RDWR);
	new_fd = open(absolute_path_to_tmp, O_RDWR | O_CREAT | O_APPEND);
	fchmod(new_fd, 0755);
	write_all_without_old_var(var_name, fd, new_fd);
	add_new_var(new_fd, var_name, var_value);
	close(fd);
	remove(absolute_path_to_rc);
	close(new_fd);
	rename(absolute_path_to_tmp, absolute_path_to_rc);
	free(absolute_path_to_tmp);
	free(absolute_path_to_rc);
}

void			my_unsetenv(char *var_name, char *p_to_rc)
{
	int 		fd;
	int 		new_fd;
	char		*absolute_path_to_rc;
	char		*absolute_path_to_tmp;

	absolute_path_to_tmp = ft_strjoin(p_to_rc, "/.tmp");
	absolute_path_to_rc = ft_strjoin(p_to_rc, "/.minishellrc");
	fd = open(absolute_path_to_rc, O_RDWR);
	new_fd = open(absolute_path_to_tmp, O_RDWR | O_CREAT | O_APPEND);
	fchmod(new_fd, 0755);
	write_all_without_old_var(var_name, fd, new_fd);
	close(fd);
	remove(absolute_path_to_rc);
	close(new_fd);
	rename(absolute_path_to_tmp, absolute_path_to_rc);
	free(absolute_path_to_tmp);
	free(absolute_path_to_rc);
}
