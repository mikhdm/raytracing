#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*d;

	dup = NULL;
	dup = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	d = dup;
	while (*s1)
		*dup++ = *s1++;
	*dup = '\0';
	return (d);
}
