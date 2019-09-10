/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:36:13 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:36:15 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

typedef struct	s_trash
{
	char		*line;
	char		**commands;
	char		**tokens;
}				t_trash;

char			**build_envp_from_rc(char *p_to_rc);
void			overwrite(char *var_name, char *var_value, char *p_to_rc);
void			add_new_var(int fd, char *var_name, char *value);
void			free_tokens(char **tokens);
void			env(char *p_to_rc);
void			my_setenv(char **tokens, char *p_to_rc);
void			my_unsetenv(char *var_name, char *p_to_rc);
void			tell_no_warranty(void);
char			*initialize(void);
void			parse_line(char *line);
void			pwd(bool color);
char			**split(const char *str);
void			exit_with_error(char *error_text);
char			**parse_one_command(char *com);

char			*cut_var(int num, char *line);
char			*get_line_from_rc(char *var, char *p_to_rc);

void			execute_command(t_trash *t, char *p_to_rc);
void			cd(char **args, char *p_to_rc);
void			echo(char *l, char *p_to_rc);
char			*delete_leading_zeros_and_tabs(const char *line);
char			*check_env(char **args, char *path_to_rc);
bool			try_to_access(char *path);

#endif
