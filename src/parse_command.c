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

static void		parse_one_command(char *com)
{
	char 		*command;
	char 		**tokens;
	int 		i;

	command = delete_leading_zeros_and_tabs(com);
	free(com);
	if (!command)
		return ;
	tokens = split(command);
	if (!ft_strcmp(tokens[0], "exit"))
		exit(0);
	if (!ft_strcmp(tokens[0], "pwd"))
		pwd(0);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

void			parse_line(char *line)
{
	char 		**commands;
	int			i;

	commands = ft_strsplit(line, ';');
	i = 0;
	while (commands[i])
	{
		parse_one_command(commands[i]);
		i++;
	}
	free(commands);
}
