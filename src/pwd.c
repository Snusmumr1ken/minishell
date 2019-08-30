#include "../includes/minishell.h"

void	pwd(bool color, t_data *data)
{
	char dir[1000];

	if (getcwd(dir, 1000) == NULL)
		exit_with_error("getcwd failed in pwd function\0", data);
	if (color)
	{
		ft_printf("\033[34m");
		write(1, dir, ft_strlen(dir));
		ft_printf("\033[0m");
	}
	else
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
}	
