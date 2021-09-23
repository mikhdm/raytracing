#include "linop.h"
#include "libft.h"
#include "parsing/validate.h"
#include <stddef.h>

t_vector3	*serialize_orient(char **strs_orient, t_vector3 *orient)
{
	size_t	strslen;

	strslen = ft_strslen(strs_orient);
	if (strslen != 3)
		return (NULL);
	if (!valid_orient((const char **)strs_orient, strslen, orient))
		return (NULL);
	return (orient);
}
