#include "../includes/minishell.h"

static void			free_tokens(char **tokens)
{
	int 			i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
}

static void			exec_coms(char **coms)
{
	int				i;
	char 			*l;
	char			**tokens;

	i = 0;
	while (coms[i])
	{
		l = delete_leading_zeros_and_tabs(coms[i]);
		if (!ft_strncmp(l, "echo ", 5) || !ft_strncmp(l, "echo\t", 5) ||
			!ft_strcmp(l, "echo"))
		{
			echo(l);
			return ;
		}
		tokens = parse_one_command(coms[i]);
		if (!tokens)
			return ;
		execute_command(tokens);
		free_tokens(tokens);
		i++;
	}
}

static void			main_loop(void)
{
	char 			*line;
	char			**coms;

	while (1)
	{
		pwd(1);
		write(1, "$ ", 2);
		get_next_line(STDIN_FILENO, &line);
		coms = ft_strsplit(line, ';');
		exec_coms(coms);
		free(line);
	}
}

int	main(void)
{
	t_data	data;

	initialize(&data);
	tell_no_warranty();
	main_loop();
	return (0);
}
