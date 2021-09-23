#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sc;

	if (!n)
		return (NULL);
	sc = (unsigned char *)s;
	while (n--)
		if (*sc++ == (unsigned char)c)
			return (--sc);
	return (NULL);
}
