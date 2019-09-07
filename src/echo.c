/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:30:23 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/09/07 12:30:25 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool		check_line_for_quotes(const char *l)
{
	int 		i;
	int 		q;

	i = 0;
	q = 0;
	while (l[i])
	{
		if (l[i] == '\"' || l[i] == '\'')
			q++;
		i++;
	}
	if (q % 2)
	{
		write(1, "minishell: echo: odd number of quotes\n", 38);
		return (0);
	}
	return (1);
}

static void		write_from_quotes(char *l, int *i)
{
	int 		pos;

	pos = *i;
	pos++;
	while (l[pos] != '\'' && l[pos] != '\"')
	{
		write(1, &l[pos], 1);
		pos++;
	}
	write(1, " ", 1);
	*i = pos;
}

void			echo(char *l)
{
	int			i;

	if (!check_line_for_quotes(l))
		return ;
	i = 4;
	while (l[i] && (l[i] == ' ' || l[i] == '\t'))
		i++;
	while (l[i])
	{
		if (l[i] == '\'' || l[i] == '\"')
			write_from_quotes(l, &i);
		else if (l[i] != ' ' && l[i] != '\t')
			write(1, &l[i], 1);
		else if (l[i - 1] != ' ' && l[i - 1] != '\t' && l[i - 1] != '\'' && l[i - 1] != '\"')
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
