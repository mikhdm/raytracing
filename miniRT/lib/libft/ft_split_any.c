#include "libft.h"
#include <stdlib.h>

size_t	ft_split_any_strslen(char const *str, char c)
{
	size_t	cnt;

	cnt = 1;
	while (*str)
	{
		if (*str == c)
			++cnt;
		++str;
	}
	return (cnt);
}

static void	*ft_split_any_free(char **strs, size_t cnt)
{
	while (cnt--)
		free(strs[cnt]);
	free(strs);
	return (NULL);
}

char	**ft_split_any(char const *s, char c)
{
	size_t		i;
	char		**strs;
	const char	*start;

	i = 0;
	start = s;
	strs = malloc(sizeof(char *) * (ft_split_any_strslen(s, c) + 1));
	if (!strs)
		return (NULL);
	while (*s)
	{
		if (*s++ == c)
		{
			strs[i] = ft_strdup_until(start, c);
			if (!strs[i])
				return (ft_split_any_free(strs, i));
			++i;
			start = s;
		}
	}
	strs[i] = ft_strdup_until(start, c);
	if (!strs[i])
		return (ft_split_any_free(strs, i));
	strs[++i] = NULL;
	return (strs);
}
