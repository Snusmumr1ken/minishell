/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:30:13 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:30:14 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool		name_exist(const char *name, char *p_to_rc)
{
	int			fd;
	int			res;
	char		*l;
	char		*line;

	line = ft_strjoin(p_to_rc, "/.minishellrc");
	fd = open(line, O_RDONLY);
	free(line);
	l = ft_strjoin(name, "=");
	while ((res = get_next_line(fd, &line)) == 1)
	{
		if (!ft_strncmp(line, l, ft_strlen(l)))
		{
			free(l);
			free(line);
			return (1);
		}
		free(line);
	}
	free(line);
	free(l);
	close(fd);
	return (0);
}

static int		check_number_of_tokens(char **tokens)
{
	int			i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

static bool		basic_checks(char **tokens, char *p_to_rc)
{
	int			var;

	var = check_number_of_tokens(tokens);
	if (var == 1)
	{
		env(p_to_rc);
		return (1);
	}
	if (var != 4)
	{
		write(2, "minishell: setenv: wrong number of params\n", 42);
		write(2, "One or three parameters.\n", 25);
		write(2, "1 - name of the system var\n", 27);
		write(2, "2 - value\n", 10);
		write(2, "3 - overwrite\n", 14);
		return (1);
	}
	return (0);
}

void			add_new_var(int fd, char *var_name, char *value)
{
	write(fd, var_name, ft_strlen(var_name));
	write(fd, "=", 1);
	write(fd, value, ft_strlen(value));
	write(fd, "\n", 1);
}

void			my_setenv(char **tokens, char *p_to_rc)
{
	bool		exist;
	int			fd;
	char		*line;

	if (basic_checks(tokens, p_to_rc))
		return ;
	exist = name_exist(tokens[1], p_to_rc);
	if (exist && ft_atoi(tokens[3]) == 1)
		overwrite(tokens[1], tokens[2], p_to_rc);
	else if (!exist)
	{
		line = ft_strjoin(p_to_rc, "/.minishellrc");
		fd = open(line, O_RDWR | O_APPEND);
		free(line);
		add_new_var(fd, tokens[1], tokens[2]);
		close(fd);
	}
}
