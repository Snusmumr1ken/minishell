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
	char 		*line;
	char 		**commands;
	char 		**tokens;
}				t_trash;

typedef struct	s_data
{
	char		*PATH;
	char 		*HOME;
	char 		*OLDPWD;
}				t_data;

void			free_tokens(char **tokens);
void			free_data(t_data *data);
void			tell_no_warranty(void);
void			initialize(t_data *data);
void			parse_line(char *line);
void			pwd(bool color, t_data *data);
char			**split(const char *str);
void			exit_with_error(char *error_text, t_data *data);
char			**parse_one_command(char *com);
void			execute_command(t_trash *t, t_data *data);
void			cd(char **args, t_data *data);
void			echo(char *l);
char			*delete_leading_zeros_and_tabs(const char *line);
char			*cut_data_home(t_data *data);
char			*check_env(char **args, t_data *data);

#endif
