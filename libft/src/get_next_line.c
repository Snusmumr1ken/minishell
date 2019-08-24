/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 12:04:38 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/02/08 11:44:05 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char			*strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}

void				c_and_c(char *to_clr, char *temp, char *str, char *buff)
{
	free(temp);
	free(to_clr);
	ft_strcat(str, buff);
	ft_memmove(str, &str[ft_strchr(str, '\n') - str + 1], BUFF_SIZE);
}

static int			read_buff(const int fd, char **line, char *str)
{
	char	buff[BUFF_SIZE + 1];
	char	*to_clr;
	char	*temp;
	int		i;

	while ((i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[i] = '\0';
		to_clr = *line;
		if (ft_strchr(buff, '\n'))
		{
			temp = ft_strsub(buff, 0, ft_strchr(buff, '\n') - buff);
			*line = strjoin(*line, temp);
			c_and_c(to_clr, temp, str, buff);
			return (1);
		}
		*line = strjoin(*line, buff);
		free(to_clr);
		if (i < BUFF_SIZE)
			return (1);
	}
	if (ft_strlen(*line) > 0)
		return (1);
	return (0);
}

static int			parse_static(char **line, char *str)
{
	char *temp;

	if (ft_strchr(str, '\n'))
	{
		temp = ft_strsub(str, 0, ft_strchr(str, '\n') - str);
		*line = ft_strdup(temp);
		free(temp);
		if (ft_strlen(str) > (ft_strchr(str, '\n') - str + 1))
			ft_memmove(str, &str[ft_strchr(str, '\n') - str + 1], BUFF_SIZE);
		else
			ft_strclr(str);
		return (1);
	}
	else
	{
		*line = ft_strdup(str);
		ft_strclr(str);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static char	str[4864][BUFF_SIZE + 1];

	if (read(fd, str[fd], 0) < 0 || fd > 4863 || line == NULL)
		return (-1);
	*line = (char*)malloc(1);
	ft_strclr(*line);
	if (str[fd] && ft_strlen(str[fd]) != 0)
	{
		if (parse_static(line, str[fd]))
			return (1);
	}
	if (read_buff(fd, line, str[fd]) != 0)
		return (1);
	return (0);
}
