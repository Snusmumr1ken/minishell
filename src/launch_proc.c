#include "../includes/minishell.h"

static void		launch_proc(t_trash *t, t_data *data)
{
	pid_t		pid;
	int			status;
	char 		*path;

	pid = fork();
	if (pid == 0)
	{
		path = check_env(t->tokens, data);
		if (path == NULL || (execve(path, t->tokens, NULL)) == -1)
		{
			free(t->line);
			free_tokens(t->commands);
			free_tokens(t->tokens);
			free_data(data);
			write(2, "minishell: command not found\n", 29);
			exit(1);
		}
	}
	else if (pid < 0)
		exit_with_error("error forking\0", data);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
}

void			execute_command(t_trash *t, t_data *data)
{
	if (!ft_strcmp(t->tokens[0], "pwd"))
		pwd(0, data);
	else if (!ft_strcmp(t->tokens[0], "cd"))
		cd(t->tokens, data);
	else if (!ft_strcmp(t->tokens[0], "clear"))
		write(1, "\33[H\33[2J", 7);
	else
		launch_proc(t, data);
}
