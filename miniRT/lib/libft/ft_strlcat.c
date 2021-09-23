#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	dstsizeinit;

	srcsize = ft_strlen(src);
	dstsizeinit = ft_strlen(dst);
	if (dstsizeinit >= dstsize)
		return (dstsize + srcsize);
	dst += dstsizeinit;
	dstsize -= dstsizeinit;
	while (--dstsize && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (dstsizeinit + srcsize);
}
