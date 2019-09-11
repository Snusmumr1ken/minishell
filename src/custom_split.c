/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:28:43 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/07/17 14:28:48 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

static int		ft_count_words(const char *str)
{
	int			word;
	int			i;

	i = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t') &&
			(str[i + 1] != ' ' && str[i + 1] != '\t'))
			word++;
		i++;
	}
	if (str[0] != '\0')
		word++;
	return (word);
}

static char		*ft_word(const char *str, int *i)
{
	char		*s;
	int			k;

	if (!(s = (char *)malloc(sizeof(s) * (ft_strlen(str)))))
		return (NULL);
	k = 0;
	while (str[*i] != ' ' && str[*i] != '\t' && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	while ((str[*i] == ' ' || str[*i] == '\t') && str[*i])
		*i += 1;
	return (s);
}

char			**split(const char *str)
{
	int			i;
	int			j;
	int			wrd;
	char		**s;

	i = 0;
	j = 0;
	wrd = ft_count_words(str);
	if (!(s = (char **)malloc(sizeof(s) * (wrd + 1))))
		return (NULL);
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	while (j < wrd && str[i])
	{
		s[j] = ft_word(str, &i);
		j++;
	}
	s[j] = NULL;
	return (s);
}

char			*delete_leading_zeros_and_tabs(const char *line)
{
	char		*new_str;
	short		i;
	short		j;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (NULL);
	new_str = (char*)malloc(ft_strlen(line) - i + 1);
	j = 0;
	while (line[i])
	{
		new_str[j] = line[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char			**parse_one_command(char *com)
{
	char		*command;
	char		**tokens;

	command = delete_leading_zeros_and_tabs(com);
	if (!command)
		return (NULL);
	tokens = split(command);
	free(command);
	return (tokens);
}
