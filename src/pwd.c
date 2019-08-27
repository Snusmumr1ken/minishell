#include "../includes/minishell.h"

void	pwd(void)
{
	char dir[100];

	getcwd(dir, 100);
	write(1, dir, ft_strlen(dir));
}	
