#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

void			tell_no_warranty(void);
void			parse_line(char *line);
void			pwd(bool color);
char			**split(const char *str);
void			exit_with_error(char *error_text);
void			parse_one_command(char *com);
void			execute_command(char **tokens);
void			launch_proc(char **args);

#endif
