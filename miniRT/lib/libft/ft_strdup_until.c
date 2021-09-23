#include "libft.h"
#include <stdlib.h>

char	*ft_strdup_until(const char *s1, const char sym)
{
	char	*dup;
	char	*d;

	dup = malloc((ft_strlen_until(s1, sym) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	d = dup;
	while (*s1 && *s1 != sym)
		*dup++ = *s1++;
	*dup = '\0';
	return (d);
}
