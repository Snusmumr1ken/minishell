#include "../includes/minishell.h"

void		execute_command(char **tokens)
{
	if (!ft_strcmp(tokens[0], "exit"))
		exit(0);
	if (!ft_strcmp(tokens[0], "pwd"))
		pwd(0);
	else
		launch_proc(tokens);
}

void		launch_proc(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
			exit_with_error("unable to run new process\0");
	}
	else if (pid < 0)
		exit_with_error("error forking\0");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
}