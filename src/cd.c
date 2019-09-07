/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:29:32 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:29:33 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*cut_data_home(t_data *data)
{
	char 		*home;
	int 		len;
	int 		i;
	int 		j;

	len = ft_strlen(data->HOME) - 4;
	home = (char*)malloc(len);
	home[len - 1] = '\0';
	i = 5;
	j = 0;
	while (data->HOME[i])
	{
		home[j] = data->HOME[i];
		i++;
		j++;
	}
	return (home);
}

static void		move_home(t_data *data)
{
	char 		*home;

	home = cut_data_home(data);
	if (chdir(home) != 0)
		write(2, "minishell: cd: unable to move to the home dir\n", 46);
	free(home);
}

void		create_path(char *path, char *p, char *home)
{
	int 	i;
	int 	j;

	i = 5;
	j = 0;
	while (home[i])
	{
		path[j] = home[i];
		i++;
		j++;
	}
	i = 1;
	while (p[i])
	{
		path[j] = p[i];
		i++;
		j++;
	}
}

void		move_by_path(char *p, t_data *data)
{
	char	*path;
	char 	*home;
	int 	len;

	if (!ft_strncmp(p, "~", 1))
	{
		home = cut_data_home(data);
		len = ft_strlen(home) + ft_strlen(p);
		free(home);
		path = (char*)malloc(len);
		path[len - 1] = '\0';
		create_path(path, p, data->HOME);
	}
	else
		path = ft_strdup(p);
	if (chdir(path) != 0)
		write(2, "minishell: cd: unable to move there\n", 36);
	free(path);
}

static void		call_move_home(t_data *data)
{
	char 		*p;

	p = cut_data_home(data);
	free(data->OLDPWD);
	data->OLDPWD = ft_strdup(p);
	move_home(data);
	free(p);
}

void			cd(char **args, t_data *data)
{
	if (args[1] == NULL)
		call_move_home(data);
	else if (!ft_strcmp(args[1], "-"))
	{
		if (!ft_strcmp(data->OLDPWD, data->HOME))
			call_move_home(data);
		move_by_path(data->OLDPWD, data);
	}
	else if (args[2] != NULL)
		write(2, "minishell: cd: too many arguments\n", 34);
	else
	{
		free(data->OLDPWD);
		data->OLDPWD = ft_strdup(args[1]);
		move_by_path(args[1], data);
	}
}
