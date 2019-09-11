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

static void		run_child_process(t_trash *t, char *p_to_rc, char **envp)
{
	char 		*path;

	if (try_to_access(t->tokens[0]))
		path = ft_strdup(t->tokens[0]);
	else if (!ft_strncmp(t->tokens[0], "$", 1))
		path = check_env_for_var(t->tokens[0], p_to_rc);
	else
		path = check_env(t->tokens, p_to_rc);
	if (path == NULL || (execve(path, t->tokens, envp)) == -1)
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
	char 		**envp;

	envp = build_envp_from_rc(p_to_rc);
	pid = fork();
	if (pid == 0)
		run_child_process(t, p_to_rc, envp);
	else if (pid < 0)
		exit_with_error("error forking\0");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		free_tokens(envp);
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
	else if (!ft_strcmp(t->tokens[0], "unsetenv"))
		my_unsetenv(t->tokens[1], p_to_rc);
	else if (!ft_strcmp(t->tokens[0], "cd"))
		cd(t->tokens, p_to_rc);
	else if (!ft_strcmp(t->tokens[0], "clear"))
		write(1, "\33[H\33[2J", 7);
	else
		launch_proc(t, p_to_rc);
}
