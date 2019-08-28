#include "../includes/minishell.h"

static bool		check_line_for_quotes(const char *l)
{
	int 		i;
	int 		q;

	i = 0;
	q = 0;
	while (l[i])
	{
		if (l[i] == '\"' || l[i] == '\'')
			q++;
		i++;
	}
	if (q % 2)
	{
		write(1, "minishell: echo: odd number of quotes\n", 38);
		return (0);
	}
	return (1);
}

void			echo(char *l)
{
	int			i;

	if (!check_line_for_quotes(l))
		return ;
	i = 4;
	while (l[i] && (l[i] == ' ' || l[i] == '\t'))
		i++;
	while (l[i])
	{
		if (l[i] == '\'' || l[i] == '\"')
		{
			i++;
			while (l[i] != '\'' && l[i] != '\"')
			{
				write(1, &l[i], 1);
				i++;
			}
			write(1, " ", 1);
		}
		else if (l[i] != ' ' && l[i] != '\t')
			write(1, &l[i], 1);
		else if (l[i - 1] != ' ' && l[i - 1] != '\t' && l[i - 1] != '\'' && l[i - 1] != '\"')
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
