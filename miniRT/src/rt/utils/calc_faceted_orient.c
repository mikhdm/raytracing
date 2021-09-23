#include "linop.h"
#include "libft.h"

t_vector3	calc_faceted_orient(t_vector3 *dirvec, t_vector3 *orient)
{
	t_vector3	vec;
	t_vector3	facing_ratio;

	vec = *orient;
	facing_ratio = cmultvec3(-1, dirvec);
	facing_ratio = normvec3(&facing_ratio);
	if (ft_flt(dot3(&facing_ratio, orient), 0))
		vec = cmultvec3(-1, orient);
	return (vec);
}
