#include "../includes/minishell.h"

static char		*cut_data_home(t_data *data)
{
	char 		*home;
	int 		len;
	int 		i;
	int 		j;

	len = ft_strlen(data->HOME) - 5;
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

	if (p[0] == '~')
	{
		path = (char*)malloc(ft_strlen(data->HOME) + ft_strlen(p));
		create_path(path, p, data->HOME);
	}
	else
		path = ft_strdup(p);
	if (chdir(path) != 0)
		write(2, "minishell: cd: unable to move there\n", 36);
	free(path);
}

void			cd(char **args, t_data *data)
{
	if (args[1] == NULL)
		move_home(data);
	else if (args[2] != NULL)
		write(2, "minishell: cd: too many arguments\n", 34);
	else
		move_by_path(args[1], data);
}
