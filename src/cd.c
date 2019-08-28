#include "../includes/minishell.h"

void	cd(char **args)
{
	if (args[2] != NULL)
		write(2, "minishell: cd: too many arguments\n", 34);
	else if (args[1] == NULL)
	{
		if (chdir("/home/odmin/") != 0)
			write(2, "minishell: cd: unable to move to the home dir\n", 46);
	}
	else
	{
		if (chdir(args[1]) != 0)
			write(2, "minishell: cd: unable to move there\n", 36);
	}
}
