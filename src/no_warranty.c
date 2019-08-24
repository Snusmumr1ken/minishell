#include <unistd.h>

void	tell_no_warranty(void)
{
	write(1, "This minishell was created by anyvchyk.\n", 40);
	write(1, "And it goes with ABSOLUTELY NO WARRANTY.\n", 41);
	write(1, "\n", 1);
}
