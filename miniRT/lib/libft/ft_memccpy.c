#include <stdlib.h>
#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;

	d = dst;
	while (n--)
	{
		*d = *(unsigned char *)src;
		if (*d == (unsigned char)c)
			return (++d);
		++d;
		++src;
	}
	return (NULL);
}
