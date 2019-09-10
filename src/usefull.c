/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:30:56 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:30:58 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void			exit_with_error(char *error_text)
{
	write(2, "minishell: ", 11);
	write(2, error_text, ft_strlen(error_text));
	write(2, "\n", 1);
	exit(2);
}

static int		get_num_of_vars(char *p_to_rc)
{
	char 		*rc;
	int 		fd;
	int 		num;
	char 		*line;
	int 		res;

	rc = ft_strjoin(p_to_rc, "/.minishellrc");
	fd = open(rc, O_RDONLY);
	num = 0;
	while ((res = get_next_line(fd, &line)) == 1)
	{
		free(line);
		num++;
	}
	free(line);
	free(rc);
	close(fd);
	return (num);
}

static void		fill_envp(char *p_to_rc, char **envp)
{
	char 		*rc;
	int 		fd;
	char 		*line;
	int 		res;
	int 		i;

	rc = ft_strjoin(p_to_rc, "/.minishellrc");
	fd = open(rc, O_RDONLY);
	i = 0;
	while ((res = get_next_line(fd, &line)) == 1)
	{
		envp[i] = ft_strdup(line);
		free(line);
		i++;
	}
	free(line);
	free(rc);
	close(fd);
}

char			**build_envp_from_rc(char *p_to_rc)
{
	char 		**envp;
	int 		size;

	size = get_num_of_vars(p_to_rc);
	envp = (char**)malloc(sizeof(envp) * (size + 1));
	envp[size] = NULL;
	fill_envp(p_to_rc, envp);
	return (envp);
}
