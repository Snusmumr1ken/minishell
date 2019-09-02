#include "../includes/minishell.h"

static bool		name_exist(const char *name)
{
	int			fd;
	int 		res;
	char 		*l;
	char 		*line;

	l = ft_strjoin(name, "=");
	fd = open(".minishellrc", O_RDONLY);
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

static bool		basic_checks(char **tokens)
{
	int 		var;

	var = check_number_of_tokens(tokens);
	if (var == 1)
	{
		env();
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

void			my_setenv(char **tokens)
{
	bool		exist;
	if (basic_checks(tokens))
		return ;
	exist = name_exist(tokens[1]);
	if (exits && ft_atoi(tokens[3]) == 1)
		ft_printf("It finds and overwrite\n");
	else if (!exist)
		ft_printf("Create new var\n");
}
