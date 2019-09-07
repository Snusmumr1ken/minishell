#include "../includes/minishell.h"

void		add_new_var(char **tokens)
{
	int 	fd;

	fd = open(".minishellrc", O_RDWR);
	write(fd, tokens[1], ft_strlen(tokens[1]));
	write(fd, "=", 1);
	write(fd, tokens[2], ft_strlen(tokens[2]));
	write(fd, "\n", 1);
	close(fd);
}
