#include "libft.h"
#include "linop.h"
#include <stddef.h>

short	valid_orient(const char **strs_orient, size_t strslen,
			t_vector3 *orient)
{
	const char	*str;
	size_t		i;

	i = 0;
	str = NULL;
	while (i < strslen)
	{
		str = strs_orient[i++];
		if (!str || !*str)
			return (FALSE);
		if (!ft_isfloatable(str))
			return (FALSE);
	}
	orient->x = ft_atof(strs_orient[0]);
	orient->y = ft_atof(strs_orient[1]);
	orient->z = ft_atof(strs_orient[2]);
	if (ft_flt(orient->x, -1) || ft_fgt(orient->x, 1)
		|| ft_flt(orient->y, -1) || ft_fgt(orient->y, 1)
		|| ft_flt(orient->z, -1) || ft_fgt(orient->z, 1))
		return (FALSE);
	*orient = normvec3(orient);
	if (!ft_fequal(hypotvec3(orient), 1))
		return (FALSE);
	return (TRUE);
}
