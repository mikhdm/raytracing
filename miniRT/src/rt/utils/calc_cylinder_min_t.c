#include "canvas.h"
#include "utils.h"
#include <math.h>

double	calc_cylinder_min_t(t_vector3 *p0, t_pair_double const *values_t,
			t_vector3 *dirvec, t_cylinder *cylinder)
{
	t_pair_double	values_m;
	t_vector3		co;

	if (isinf(values_t->first) && isinf(values_t->second))
		return (INFINITY);
	co = diffvec3(p0, &cylinder->center);
	values_m.first = dot3(&co, &cylinder->orient)
		+ values_t->first * dot3(dirvec, &cylinder->orient);
	values_m.second = dot3(&co, &cylinder->orient)
		+ values_t->second * dot3(dirvec, &cylinder->orient);
	if (values_m.first * 2 >= -cylinder->height
		&& values_m.first * 2 <= cylinder->height)
	{
		if (values_m.second * 2 >= -cylinder->height
			&& values_m.second * 2 <= cylinder->height)
			return (calc_min_t(*values_t));
		return (values_t->first);
	}
	else if (values_m.second * 2 >= -cylinder->height
		&& values_m.second * 2 <= cylinder->height)
		return (values_t->second);
	return (INFINITY);
}
