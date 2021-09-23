#include "linop.h"
#include "libft.h"
#include <stddef.h>
#include <math.h>

/*
* valid_point3 - sets into point struct correct 3D point placement if valid.
*/
short	valid_point3(const char **strs_point, size_t strslen, t_vector3 *point)
{
	const char	*str;
	size_t		i;

	str = NULL;
	i = 0;
	while (i < strslen)
	{
		str = strs_point[i++];
		if (!str || !*str)
			return (FALSE);
		if (!ft_isfloatable(str))
			return (FALSE);
	}
	point->x = ft_atof(strs_point[0]);
	point->y = ft_atof(strs_point[1]);
	point->z = ft_atof(strs_point[2]);
	if ((isnan(point->x) || isinf(point->x))
		|| (isnan(point->y) || isinf(point->y))
		|| (isnan(point->z) || isinf(point->z)))
		return (FALSE);
	return (TRUE);
}
