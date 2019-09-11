/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:29:31 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/11 10:29:32 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		create_path(char *path, char *p, char *home)
{
	int		i;
	int		j;

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

char		*manage_tilde(char *p, char *p_to_rc)
{
	char	*tmp;
	char	*home;
	int		len;

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
