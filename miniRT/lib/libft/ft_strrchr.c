#include <stdlib.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*sp;

	sp = (char *)s;
	sp = sp + ft_strlen(s);
	while (sp != s)
	{
		if (*sp == (char)c)
			return (sp);
		--sp;
	}
	if (*sp == (char)c)
		return (sp);
	return (NULL);
}
