#include "../includes/minishell.h"

void	parse_line(char *line)
{
	if (!ft_strcmp(line, "exit"))
		exit(0);
}

void	main_loop(void)
{
	char *line;

	while(1)
	{
		write(1, "$> ", 3);
		get_next_line(STDIN_FILENO, &line);
		parse_line(line);
		free(line);
	}
}

int	main(void)
{
	tell_no_warranty();
	main_loop();
	return (0);
}

