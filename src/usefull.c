#include "../includes/minishell.h"

void			free_tokens(char **tokens)
{
	int 			i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
}

void			free_data(t_data *data)
{
	if (data->HOME)
		free(data->HOME);
	if (data->PATH)
		free(data->PATH);
	if (data->OLDPWD)
		free(data->OLDPWD);
}

void			exit_with_error(char *error_text, t_data *data)
{
	write(2, "minishell: ", 11);
	write(2, error_text, ft_strlen(error_text));
	write(2, "\n", 1);
	free_data(data);
	exit(2);
}