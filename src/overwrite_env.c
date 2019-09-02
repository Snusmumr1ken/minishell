#include "../includes/minishell.h"

void			overwrite(char **tokens)
{
	int 		fd;
	int 		new_fd;

	fd = open(".minishellrc", O_RDWR);
	new_fd = open("")
}