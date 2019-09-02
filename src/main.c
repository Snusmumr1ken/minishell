#include "../includes/minishell.h"

void			free_tokens(char **tokens)
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

static bool			manage_echo(char **coms, int i)
{
	char 			*l;

	l = delete_leading_zeros_and_tabs(coms[i]);
	if (!ft_strncmp(l, "echo ", 5) || !ft_strncmp(l, "echo\t", 5) ||
		!ft_strcmp(l, "echo"))
	{
		echo(l);
		free(l);
		return (1);
	}
	if (l)
		free(l);
	return (0);
}

static void			manage_exit(char **coms, char **tokens, t_data *data, char *line)
{
	if (!ft_strcmp(tokens[0], "exit"))
	{
		free(line);
		free_data(data);
		free_tokens(tokens);
		free(coms);
		exit(0);
	}
}

static void			exec_coms(char **coms, t_data *data, char *line)
{
	int				i;
	char			**tokens;

	i = -1;
	while (coms[++i])
	{
		if (manage_echo(coms, i))
		{
			free(coms[i]);
			continue ;
		}
		tokens = parse_one_command(coms[i]);
		if (!tokens)
			return ;
		manage_exit(coms, tokens, data, line);
		execute_command(tokens, data);
		free_tokens(tokens);
	}
}

static void			main_loop(t_data *data)
{
	char 			*line;
	char			**coms;

	while (1)
	{
		pwd(1, data);
		write(1, "$ ", 2);
		get_next_line(STDIN_FILENO, &line);
		coms = ft_strsplit(line, ';');
		exec_coms(coms, data, line);
		free(line);
		free(coms);
	}
}

int	main(void)
{
	t_data	data;

	write(1, "\33[H\33[2J", 7);
	initialize(&data);
	tell_no_warranty();
	main_loop(&data);
	return (0);
}
