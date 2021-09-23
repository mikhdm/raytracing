#include "parsing/validate.h"
#include "libft.h"
#include <stddef.h>

int	*serialize_rgb(char **strs_rgb, int *argb)
{
	size_t	strslen;

	strslen = ft_strslen(strs_rgb);
	if (strslen != 3)
		return (NULL);
	if (!valid_rgb((const char **)strs_rgb, strslen, argb))
		return (NULL);
	return (argb);
}
