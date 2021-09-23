#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	size_t	s1size;
	size_t	s2size;

	buf = NULL;
	s1size = ft_strlen(s1);
	s2size = ft_strlen(s2);
	buf = malloc(sizeof(char) * (s1size + s2size + 1));
	if (!buf)
		return (NULL);
	buf = ft_memcpy(buf, s1, s1size);
	buf += s1size;
	buf = ft_memcpy(buf, s2, s2size);
	buf += s2size;
	*buf = '\0';
	buf -= s1size + s2size;
	return (buf);
}
