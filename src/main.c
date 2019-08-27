#include "../includes/minishell.h"

void	parse_line(char *line)
{
	if (!ft_strcmp(line, "exit"))
		exit(0);
	if (!ft_strcmp(line, "cd"))
		chdir("/");
	if (!ft_strcmp(line, "pwd"))
	{
		pwd();
		write(1, "\n", 1);
	}
}

void	main_loop(void)
{
	char *line;

	while(1)
	{
		ft_printf("\033[34m");
		pwd();
		ft_printf("\033[0m");
		write(1, "$ ", 2);
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

