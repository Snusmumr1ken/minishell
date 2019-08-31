#include "../includes/minishell.h"

static void		launch_proc(char **args, t_data *data)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			write(2, "command not found\n", 18);
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

void			execute_command(char **tokens, t_data *data)
{
	if (!ft_strcmp(tokens[0], "exit"))
	{
		free_data(data);
		exit(0);
	}
	else if (!ft_strcmp(tokens[0], "pwd"))
		pwd(0, data);
	else if (!ft_strcmp(tokens[0], "cd"))
		cd(tokens, data);
	else if (!ft_strcmp(tokens[0], "clear"))
		write(1, "\33[H\33[2J", 7);
	else
		launch_proc(tokens, data);
}
