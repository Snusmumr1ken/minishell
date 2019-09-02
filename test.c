#include <stdlib.h>

int			ft_strlen(const char *str)
{
	int		size;

	if (!str)
		return (0);
	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}

static int		ft_count_words(const char *str, char c)
{
	int			word;
	int			i;

	i = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			word++;
		i++;
	}
	if (str[0] != '\0')
		word++;
	return (word);
}

static char		*ft_word(const char *str, char c, int *i)
{
	char		*s;
	int			k;

	if (!(s = (char *)malloc(sizeof(s) * (ft_strlen(str)))))
		return (NULL);
	k = 0;
	while (str[*i] != c && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	while (str[*i] == c && str[*i])
		*i += 1;
	return (s);
}

static char			**ft_strsplit(const char *str, char c)
{
	int			i;
	int			j;
	int			wrd;
	char		**s;

	i = 0;
	j = 0;
	wrd = ft_count_words(str, c);
	if (!(s = (char **)malloc(sizeof(s) * (ft_count_words(str, c) + 1))))
		return (NULL);
	while (str[i] == c && str[i])
		i++;
	while (j < wrd && str[i])
	{
		s[j] = ft_word(str, c, &i);
		j++;
	}
	s[j] = NULL;
	return (s);
}

int				main(void)
{
	char 		**s;
	char 		*line;

	line = (char*)malloc(5);
	for(int i = 0; i < 5; i++)
		line[i] = 'o';
	line[4] = '\0';
	s = ft_strsplit(line, ':');
}