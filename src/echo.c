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
	int			i;
	int			q;

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
	int			pos;

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

static char		*get_var_name(char *l, int *i)
{
	char		buff[1000];
	char		*var;
	int			k;
	int			j;

	k = *i;
	k++;
	j = 0;
	while (l[k] != ' ' && l[k] != '\t' && l[k])
	{
		buff[j] = l[k];
		k++;
		j++;
	}
	*i = k - 1;
	buff[j] = '\0';
	var = ft_strdup(buff);
	return (var);
}

static void		write_var(char *l, int *i, char *p_to_rc)
{
	char		*var;
	char		*data;
	char		*buff;

	data = get_var_name(l, i);
	buff = ft_strdup(data);
	var = get_line_from_rc(data, p_to_rc);
	free(data);
	data = cut_var(ft_strlen(buff) + 1, var);
	if (!data)
		return ;
	free(var);
	ft_printf("%s ", data);
	free(data);
}

void			echo(char *l, char *p_to_rc)
{
	int			i;

	if (!check_line_for_quotes(l))
		return ;
	i = 4;
	while (l[i] && (l[i] == ' ' || l[i] == '\t'))
		i++;
	while (l[i])
	{
		if (l[i] == '$')
			write_var(l, &i, p_to_rc);
		else if (l[i] == '\'' || l[i] == '\"')
			write_from_quotes(l, &i);
		else if (l[i] != ' ' && l[i] != '\t')
			write(1, &l[i], 1);
		else if (l[i - 1] != ' ' && l[i - 1] != '\t' &&
			l[i - 1] != '\'' && l[i - 1] != '\"')
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
