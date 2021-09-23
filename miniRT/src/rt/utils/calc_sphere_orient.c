#include <math.h>
#include "rayop.h"
#include "linop.h"

t_vector3	calc_sphere_orient(t_vector3 *point, t_sphere *sphere)
{
	t_vector3	orient;
	t_vector3	normalized;
	double		length;

	orient = diffvec3(point, &sphere->center);
	length = hypotvec3(&orient);
	normalized = cmultvec3(pow(length, -1), &orient);
	return (normalized);
}
