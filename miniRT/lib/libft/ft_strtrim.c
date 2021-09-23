#include <stdlib.h>
#include "libft.h"

static int	is_oneof(char c, char const *set)
{
	unsigned int	flag;

	flag = FALSE;
	while (*set)
		if (c == *set++)
			flag = TRUE;
	return (flag);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*out;
	char	*outp;

	start = (char *)s1;
	while (*start && is_oneof(*start, set))
		++start;
	if (!*start)
		return (ft_strdup(""));
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (is_oneof(*end, set))
		--end;
	++end;
	out = malloc(sizeof(char) * ((end - start) + 1));
	if (!out)
		return (NULL);
	outp = out;
	while (start != end)
		*outp++ = *start++;
	*outp = '\0';
	return (out);
}
