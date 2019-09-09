/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:29:50 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:29:51 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		free_trash(t_trash *t)
{
	free(t->line);
	t->line = NULL;
	free_tokens(t->commands);
	free_tokens(t->tokens);
}

static void		run_child_process(t_trash *t, char *p_to_rc)
{
	char 		*path;

	if (try_to_access(t->tokens[0]))
		path = ft_strdup(t->tokens[0]);
	else
		path = check_env(t->tokens, p_to_rc);
	if (path == NULL || (execve(path, t->tokens, NULL)) == -1)
	{
		ft_printf("minishell: command not found: %s\n", t->tokens[0]);
		free_trash(t);
		exit(1);
	}
}

static void		launch_proc(t_trash *t, char *p_to_rc)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == 0)
		run_child_process(t, p_to_rc);
	else if (pid < 0)
		exit_with_error("error forking\0");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
}

void			execute_command(t_trash *t, char *p_to_rc)
{
	if (!ft_strcmp(t->tokens[0], "pwd"))
		pwd(0);
	else if (!ft_strcmp(t->tokens[0], "env"))
		env(p_to_rc);
	else if (!ft_strcmp(t->tokens[0], "setenv"))
		my_setenv(t->tokens, p_to_rc);
	else if (!ft_strcmp(t->tokens[0], "cd"))
		cd(t->tokens, p_to_rc);
	else if (!ft_strcmp(t->tokens[0], "clear"))
		write(1, "\33[H\33[2J", 7);
	else
		launch_proc(t, p_to_rc);
}
