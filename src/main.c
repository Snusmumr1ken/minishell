#include "../includes/minishell.h"

static void			exec_coms(char **coms)
{
	int				i;
	int 			j;
	char			**tokens;

	i = 0;
	while (coms[i])
	{
		tokens = parse_one_command(coms[i]);
		execute_command(tokens);
		i++;
		j = -1;
		while (tokens[++i])
			free(tokens[i]);
		free(tokens);
		tokens = NULL;
	}
}

static void			main_loop(void)
{
	char 			*line;
	char			**coms;
	char 			**tokens;
	int 			i;

	while (1)
	{
		pwd(1);
		write(1, "$ ", 2);
		get_next_line(STDIN_FILENO, &line);
		coms = ft_strsplit(line, ';');
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
