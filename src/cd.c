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

static void		move_by_path(char **args)
{
	char	*path;
	int 	i;
	int 	j;

	if (args[1][0] != '.' && args[1][0] != '/')
	{
		path = (char*)malloc(ft_strlen(args[1]) + 2);
		path[0] = '.';
		path[1] = '/';
		i = 0;
		j = 2;
		while (args[1][i])
		{
			path[j] = args[1][i];
			i++;
			j++;
		}
	}
	if (chdir(args[1]) != 0)
		write(2, "minishell: cd: unable to move there\n", 36);
}

void			cd(char **args, t_data *data)
{
	if (args[1] == NULL)
		move_home(data);
	else if (args[2] != NULL)
		write(2, "minishell: cd: too many arguments\n", 34);
	else
		move_by_path(args);
}
