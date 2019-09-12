/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:30:39 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:30:41 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool			manage_echo(char **coms, int i, char *p_to_rc)
{
	char			*l;

	l = delete_leading_zeros_and_tabs(coms[i]);
	if (!ft_strncmp(l, "echo ", 5) || !ft_strncmp(l, "echo\t", 5) ||
		!ft_strcmp(l, "echo"))
	{
		echo(l, p_to_rc);
		free(l);
		return (1);
	}
	if (l)
		free(l);
	return (0);
}

static void			manage_exit(t_trash *t, char *p_to_rc)
{
	if (!ft_strcmp(t->tokens[0], "exit"))
	{
		free(p_to_rc);
		free(t->line);
		free_tokens(t->tokens);
		free_tokens(t->commands);
		exit(0);
	}
}

static void			exec_coms(t_trash *t, char *p_to_rc)
{
	int				i;

	i = -1;
	while (t->commands[++i])
	{
		if (manage_echo(t->commands, i, p_to_rc))
			continue ;
		t->tokens = parse_one_command(t->commands[i]);
		if (!t->tokens)
		{
			free_tokens(t->commands);
			return ;
		}
		manage_exit(t, p_to_rc);
		execute_command(t, p_to_rc);
		free_tokens(t->tokens);
	}
	free_tokens(t->commands);
}

static void			main_loop(char *path_to_rc)
{
	t_trash			t;

	while (1)
	{
		pwd(1);
		write(1, "$ ", 2);
		get_next_line(STDIN_FILENO, &t.line);
		t.commands = ft_strsplit(t.line, ';');
		exec_coms(&t, path_to_rc);
		free(t.line);
	}
}

int					main(void)
{
	char			*p_to_rc;

	write(1, "\33[H\33[2J", 7);
	p_to_rc = initialize();
	tell_no_warranty();
	main_loop(p_to_rc);
	return (0);
}
