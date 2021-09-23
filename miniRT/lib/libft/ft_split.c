#include <stdlib.h>
#include "libft.h"

static size_t	ft_split_strslen(char const *str, char c)
{
	size_t	cnt;
	int		flag;

	cnt = 0;
	flag = OUT;
	while (*str)
	{
		if (*str != c)
		{
			if (flag == OUT)
				++cnt;
			flag = IN;
		}
		else
			flag = OUT;
		++str;
	}
	return (cnt);
}

static void	ft_split_free(char **strs, size_t cnt)
{
	while (cnt--)
		free(strs[cnt]);
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**strs;

	i = 0;
	strs = malloc(sizeof(char *) * (ft_split_strslen(s, c) + 1));
	if (!strs)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			strs[i] = ft_strdup_until(s, c);
			if (!strs[i++])
			{
				ft_split_free(strs, i);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	strs[i] = NULL;
	return (strs);
}
