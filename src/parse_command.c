#include "../includes/minishell.h"

static char		*delete_leading_zeros_and_tabs(char *line)
{
	char 		*new_str;
	short		i;
	short		j;

	i = 0;
	j = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (NULL);
	new_str = (char*)malloc(ft_strlen(line) - (i + 1));
	while (line[i])
	{
		new_str[j] = line[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void			parse_line(char *line)
{
	char		*command;

	command = delete_leading_zeros_and_tabs(line);
	free(line);
	if (!command)
		return ;
	if (!ft_strncmp(command, "exit", 4) && !is_alnum(command[4]))
		exit(0);
	if (!ft_strncmp(command, "pwd", 3) && !is_alnum(command[3]))
	{
		pwd();
		write(1, "\n", 1);
	}
}
