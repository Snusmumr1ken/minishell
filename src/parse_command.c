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
	char		*line2;
	char 		**command;
	int			i;

	line2 = delete_leading_zeros_and_tabs(line);
	if (!line2)
		return ;
	command = split(line);
	if (!ft_strcmp(command[0], "exit"))
		exit(0);
	if (!ft_strcmp(command[0], "pwd"))
	{
		pwd();
		write(1, "\n", 1);
	}
	i = -1;
	while (command[++i])
		free(command[i]);
	free(command);
}
