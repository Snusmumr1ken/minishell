/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_from_rc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:47:27 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 15:47:33 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*get_line_from_rc(char *var, char *p_to_rc)
{
	int 		fd;
	int 		i;
	char		*line;
	char		*look_for;

	line = ft_strjoin(p_to_rc, "/.minishellrc");
	fd = open(line, O_RDONLY);
	free(line);
	if (fd == -1)
		exit_with_error("cant open rc file\0");
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
	return ((!ft_strlen(line)) ? NULL : line);
}

char			*cut_var(int num, char *line)
{
	char 		*var;
	int 		len;
	int 		j;

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
