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
	int 		i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	if (path1)
		free(path1);
	if (path2)
		free(path2);
}

char			*check_env(char **args)
{
	char 		**paths;
	char 		*path1;
	char		*path2;
	char 		*obj;
	int 		i;

	path1 = get_line_from_rc("PATH");
	if (!path1)
		return (NULL);
	path2 = cut_var(5, path1);
	paths = ft_strsplit(path2, ':');
	i = -1;
	while (paths[++i])
	{
		free(path1);
		path1 = ft_strjoin(paths[i], "/");
		obj = ft_strjoin(path1, args[0]);
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
