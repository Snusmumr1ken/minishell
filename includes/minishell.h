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

/*
** cd2.c
*/
void			create_path(char *path, char *p, char *home);
char			*manage_tilde(char *p, char *p_to_rc);

/*
** cd.c
** static funcs:
** 			call_move_oldpwd
** 			call_move_home
** 			move_home
** 			move_by_path
*/
void			cd(char **args, char *p_to_rc);

/*
** create_paths.c
** static funcs:
** 			free_paths
** 			call_move_oldpwd
*/
char			*check_env(char **args, char *path_to_rc);
char			*check_env_for_var(char *var, char *p_to_rc);
bool			try_to_access(char *path);

/*
** custom_split.c
** static funcs:
** 			ft_count_words
** 			*ft_word
*/
char			**split(const char *str);
char			**parse_one_command(char *com);
char			*delete_leading_zeros_and_tabs(const char *line);

/*
** echo.c
** static funcs:
** 			write_var
** 			get_var_name
** 			write_from_quotes
** 			check_line_for_quotes
*/
void			echo(char *l, char *p_to_rc);

/*
** tools.c
*/
void			pwd(bool color);
void			env(char *p_to_rc);
char			*cut_var(int num, char *line);
char			*get_line_from_rc(char *var, char *p_to_rc);

/*
** launch_proc.c
** static funcs:
** 			free_trash
** 			run_child_process
**			launch_proc
*/
void			execute_command(t_trash *t, char *p_to_rc);

/*
** main.c
** static funcs:
** 			manage_echo
** 			manage_exit
**			exec_coms
**			main_loop
**			main
*/

/*
** overwrite_env.c
** static funcs:
**			write_all_without_old_var
*/
void			my_unsetenv(char *var_name, char *p_to_rc);
void			overwrite(char *var_name, char *var_value, char *p_to_rc);

/*
** setenv.c
** static funcs:
**			name_exist
**			check_number_of_tokens
**			basic_checks
*/
void			add_new_var(int fd, char *var_name, char *value);
void			my_setenv(char **tokens, char *p_to_rc);

/*
** usefull.c
** static funcs:
**			get_num_of_vars
**			fill_envp
*/
void			free_tokens(char **tokens);
char			**build_envp_from_rc(char *p_to_rc);
void			exit_with_error(char *error_text);

void			tell_no_warranty(void);
char			*initialize(void);

#endif
