/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:29:32 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:29:33 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		create_path(char *path, char *p, char *home)
{
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	while (home[i])
	{
		path[j] = home[i];
		i++;
		j++;
	}
	i = 1;
	while (p[i])
	{
		path[j] = p[i];
		i++;
		j++;
	}
}

static char		*manage_tilde(char *p, char *p_to_rc)
{
	char		*tmp;
	char		*home;
	int 		len;

	tmp = get_line_from_rc("HOME", p_to_rc);
	home = cut_var(5, tmp);
	len = ft_strlen(home) + ft_strlen(p);
	free(tmp);
	tmp = (char*)malloc(len);
	tmp[len - 1] = '\0';
	create_path(tmp, p, home);
	free(home);
	return (tmp);
}

static void		move_by_path(char *p, char *p_to_rc)
{
	char		*path;

	if (!ft_strncmp(p, "~", 1))
		path = manage_tilde(p, p_to_rc);
	else
		path = ft_strdup(p);
	if (chdir(path) != 0)
		write(2, "minishell: cd: unable to move there\n", 36);
	free(path);
}

static void		move_home(char *p_to_rc)
{
	char		*line;
	char 		*home;

	line = get_line_from_rc("HOME", p_to_rc);
	home = cut_var(5, line);
	if (chdir(home) != 0)
		write(2, "minishell: cd: unable to move to the home dir\n", 46);
	free(home);
	free(line);
}

static void		call_move_home(char *p_to_rc)
{
	char		*line;
	char 		*home;

	line = get_line_from_rc("HOME", p_to_rc);
	home = cut_var(5, line);
	overwrite("OLDPWD", home, p_to_rc);
	move_home(p_to_rc);
	free(line);
	free(home);
}

static void		call_move_oldpwd(char *p_to_rc)
{
	char		*i;
	char		*j;
	char		*oldpwd;
	char 		*home;

	i = get_line_from_rc("HOME", p_to_rc);
	j = get_line_from_rc("OLDPWD", p_to_rc);
	home = cut_var(5, i);
	oldpwd = cut_var(7, j);
	free(i);
	free(j);
	if (!ft_strcmp(oldpwd, home))
		call_move_home(p_to_rc);
	move_by_path(oldpwd, p_to_rc);
}

void			cd(char **args, char *p_to_rc)
{
	if (args[1] == NULL)
		call_move_home(p_to_rc);
	else if (!ft_strcmp(args[1], "-"))
		call_move_oldpwd(p_to_rc);
	else if (args[2] != NULL)
		write(2, "minishell: cd: too many arguments\n", 34);
	else
	{
		overwrite("OLDPWD", args[1], p_to_rc);
		move_by_path(args[1], p_to_rc);
	}
}
