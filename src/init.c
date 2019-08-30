#include "../includes/minishell.h"

static void			set_data_from_sys(t_data *data)
{
	extern char		**environ;
	int				i;

	i = -1;
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], "PATH=", 5))
			data->PATH = ft_strdup(environ[i]);
		else if (!ft_strncmp(environ[i], "HOME=", 5))
			data->HOME = ft_strdup(environ[i]);
		else if (!ft_strncmp(environ[i], "PWD=", 4))
			data->PWD = ft_strdup(environ[i]);
	}
}

static void			creat_minishellrc(t_data *data)
{
	int 			fd;

	fd = open(".minishellrc", O_WRONLY | O_CREAT);
	if (fd == -1)
		exit_with_error("minishellrc is not present, but it also cannot be created\0", data);
	write(fd, data->PWD, ft_strlen(data->PWD));
	write(fd, "\n", 1);
	write(fd, data->HOME, ft_strlen(data->HOME));
	write(fd, "\n", 1);
	write(fd, data->PATH, ft_strlen(data->PATH));
	write(fd, "\n", 1);
}

static void			init_from_rc(t_data *data)
{
	int 			fd;
	int				res;
	char			*line;

	fd = open(".minishellrc", O_RDONLY);
	if (fd == -1)
		exit_with_error("minishellrc is present, but I can't read from it\0", data);
	while ((res = get_next_line(fd, &line)) == 1)
	{
		if (!ft_strncmp(line, "PATH=", 5))
			data->PATH = ft_strdup(line);
		else if (!ft_strncmp(line, "HOME=", 5))
			data->HOME = ft_strdup(line);
		else if (!ft_strncmp(line, "PWD=", 4))
			data->PWD = ft_strdup(line);
		free(line);
	}
	free(line);
}

void				initialize(t_data *data)
{
	data->PATH = NULL;
	data->HOME = NULL;
	data->PWD = NULL;

	if (access(".minishellrc", F_OK) == -1)
	{
		set_data_from_sys(data);
		creat_minishellrc(data);
	}
	else
		init_from_rc(data);
}