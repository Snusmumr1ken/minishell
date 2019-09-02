#include "../includes/minishell.h"

static char		*cut_data_path(t_data *data)
{
	char 		*path;
	int 		len;
	int 		i;
	int 		j;

	len = ft_strlen(data->PATH) - 4;
	path = (char*)malloc(len);
	path[len - 1] = '\0';
	i = 5;
	j = 0;
	while (data->PATH[i])
	{
		path[j] = data->PATH[i];
		i++;
		j++;
	}
	return (path);
}

static bool		try_to_access(char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	else
		return (1);
}

static void		free_paths(char **paths, char *path)
{
	int 		i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	if (path)
		free(path);
}

char			*check_env(char **args, t_data *data)
{
	char 		**paths;
	char 		*path;
	char 		*obj;
	int 		i;

	path = cut_data_path(data);
	paths = ft_strsplit(path, ':');
	i = -1;
	while (paths[++i])
	{
		free(path);
		path = ft_strjoin(paths[i], "/");
		obj = ft_strjoin(path, args[0]);
		if (try_to_access(obj))
		{
			free_paths(paths, path);
			return (obj);
		}
		free(path);
		path = NULL;
		free(obj);
	}
	free_paths(paths, path);
	return (NULL);
}