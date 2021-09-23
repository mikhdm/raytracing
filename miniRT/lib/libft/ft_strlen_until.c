#include <stddef.h>

size_t	ft_strlen_until(const char *s, const char sym)
{
	size_t	i;

	i = 0;
	while (*s && (*s != sym))
	{
		++i;
		++s;
	}
	return (i);
}
