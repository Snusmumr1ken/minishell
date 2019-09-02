#include "../includes/minishell.h"

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

static void			manage_exit(t_trash *t, t_data *data)
{
	if (!ft_strcmp(t->tokens[0], "exit"))
	{
		free(t->line);
		free_data(data);
		free_tokens(t->tokens);
		free_tokens(t->commands);
		exit(0);
	}
}

static void			exec_coms(t_trash *t, t_data *data)
{
	int				i;

	i = -1;
	while (t->commands[++i])
	{
		if (manage_echo(t->commands, i))
			continue ;
		t->tokens = parse_one_command(t->commands[i]);
		if (!t->tokens)
			return ;
		manage_exit(t, data);
		execute_command(t, data);
		free_tokens(t->tokens);
	}
	free_tokens(t->commands);
}

static void			main_loop(t_data *data)
{
	t_trash			t;

	while (1)
	{
		pwd(1, data);
		write(1, "$ ", 2);
		get_next_line(STDIN_FILENO, &t.line);
		t.commands = ft_strsplit(t.line, ';');
		exec_coms(&t, data);
		free(t.line);
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
