#include "linop.h"
#include "libft.h"
#include "parsing/validate.h"
#include <stddef.h>

t_vector3	*serialize_point(char **strs_point, t_vector3 *point)
{
	size_t	strslen;

	strslen = ft_strslen(strs_point);
	if (strslen != 3)
		return (NULL);
	if (!valid_point3((const char **)strs_point, strslen, point))
		return (NULL);
	return (point);
}
