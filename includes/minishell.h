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

void			overwrite(char **tokens);
void			add_new_var(int fd, char **tokens);
void			free_tokens(char **tokens);
void			env(void);
void			my_setenv(char **tokens);
void			tell_no_warranty(void);
void			initialize(void);
void			parse_line(char *line);
void			pwd(bool color);
char			**split(const char *str);
void			exit_with_error(char *error_text);
char			**parse_one_command(char *com);

char			*cut_var(int num, char *line);
char			*get_line_from_rc(char *var);

void			execute_command(t_trash *t);
void			cd(char **args);
void			echo(char *l);
char			*delete_leading_zeros_and_tabs(const char *line);
char			*check_env(char **args);
bool			try_to_access(char *path);

#endif
