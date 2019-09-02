#include "../includes/minishell.h"

char		*delete_leading_zeros_and_tabs(const char *line)
{
	char 		*new_str;
	short		i;
	short		j;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (NULL);
	new_str = (char*)malloc(ft_strlen(line) - i + 1);
	j = 0;
	while (line[i])
	{
		new_str[j] = line[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char		**parse_one_command(char *com)
{
	char 		*command;
	char 		**tokens;

	command = delete_leading_zeros_and_tabs(com);
	if (!command)
		return (NULL);
	tokens = split(command);
	free(command);
	return (tokens);
}
