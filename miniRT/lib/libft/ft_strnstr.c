#include <stdlib.h>
#include "libft.h"

static char	*ft_strstr(
		const char *haystack,
		const char *needle,
		const char *end)
{
	char	*str;
	char	*key;

	while (haystack != end)
	{
		str = (char *)haystack;
		key = (char *)needle;
		while ((str != end) && *key)
		{
			if (*str != *key)
				break ;
			++str;
			++key;
		}
		if (!*key)
			return ((char *)haystack);
		++haystack;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*end;
	size_t	hsize;
	char	*substr;

	if (!*needle)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	hsize = ft_strlen(haystack);
	end = (char *)(haystack + hsize);
	if (len < hsize)
		end = (char *)(haystack + len);
	substr = ft_strstr(haystack, needle, end);
	if (substr)
		return (substr);
	return (NULL);
}
