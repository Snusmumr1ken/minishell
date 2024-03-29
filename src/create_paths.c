/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pathes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:30:18 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:30:20 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool			try_to_access(char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	else
		return (1);
}

static void		free_paths(char **paths, char *path1, char *path2)
{
	int			i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	if (path1)
		free(path1);
	if (path2)
		free(path2);
}

static char		*try_paths_loop(char *path1,
		char **paths, char *path2, char *arg)
{
	int			i;
	char		*obj;

	i = -1;
	while (paths[++i])
	{
		free(path1);
		path1 = ft_strjoin(paths[i], "/");
		obj = ft_strjoin(path1, arg);
		if (try_to_access(obj))
		{
			free_paths(paths, path1, path2);
			return (obj);
		}
		free(path1);
		path1 = NULL;
		free(obj);
	}
	free_paths(paths, path1, path2);
	return (NULL);
}

char			*check_env(char **args, char *path_to_rc)
{
	char		**paths;
	char		*path1;
	char		*path2;

	path1 = get_line_from_rc("PATH", path_to_rc);
	if (!path1)
	{
		free(path1);
		return (NULL);
	}
	path2 = cut_var(5, path1);
	paths = ft_strsplit(path2, ':');
	return (try_paths_loop(path1, paths, path2, args[0]));
}

char			*check_env_for_var(char *var, char *p_to_rc)
{
	char		*tmp;
	char		*data;

	var += 1;
	tmp = get_line_from_rc(var, p_to_rc);
	if (tmp == NULL)
		return (NULL);
	data = cut_var(ft_strlen(var) + 1, tmp);
	free(tmp);
	var -= 1;
	return (data);
}
