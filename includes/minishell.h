#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

void			tell_no_warranty(void);
void			parse_line(char *line);
void			pwd(void);
char			**split(const char *str);

#endif
