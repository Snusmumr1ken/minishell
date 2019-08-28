#include "../includes/minishell.h"

static void			main_loop(void)
{
	char *line;

	while(1)
	{
		pwd(1);
		write(1, "$ ", 2);
		get_next_line(STDIN_FILENO, &line);
		parse_line(line);
		free(line);
	}
}

void			exit_with_error(char *error_text)
{
	write(2, "minishell: ", 11);
	write(2, error_text, ft_strlen(error_text));
	write(2, "\n", 1);
	exit(2);
}

int	main(void)
{
	tell_no_warranty();
	main_loop();
	return (0);
}
