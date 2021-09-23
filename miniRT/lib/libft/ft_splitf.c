#include "libft.h"
#include <stddef.h>

static size_t	ft_splitf_strslen(char const *str, int (*f)(int))
{
	size_t	cnt;
	int		flag;

	cnt = 0;
	flag = OUT;
	while (*str)
	{
		if (!(*f)(*str))
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

static size_t	ft_splitf_strlen(char const *str, int (*f)(int))
{
	size_t	cnt;

	cnt = 0;
	while (*str && (!(*f)(*str)))
	{
		++str;
		++cnt;
	}
	return (cnt);
}

static char	*ft_splitf_strdup(char const *str, int (*f)(int))
{
	char	*s;
	char	*start;

	s = malloc(sizeof(char) * (ft_splitf_strlen(str, f) + 1));
	if (!s)
		return (NULL);
	start = s;
	while (*str && !(*f)(*str))
		*s++ = *str++;
	*s = '\0';
	return (start);
}

static void	ft_splitf_free(char **strs, size_t cnt)
{
	while (cnt--)
		free(strs[cnt]);
	free(strs);
}

char	**ft_splitf(char const *s, int (*f)(int))
{
	size_t	i;
	char	**strs;

	i = 0;
	strs = malloc(sizeof(char *) * (ft_splitf_strslen(s, f) + 1));
	if (!strs)
		return (NULL);
	while (*s)
	{
		if (!(*f)(*s))
		{
			strs[i] = ft_splitf_strdup(s, f);
			if (!strs[i++])
			{
				ft_splitf_free(strs, i);
				return (NULL);
			}
			while (*s && !((*f)(*s)))
				s++;
		}
		else
			s++;
	}
	strs[i] = NULL;
	return (strs);
}
