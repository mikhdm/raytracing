#include "canvas.h"
#include "linop.h"

t_vector3	calc_triangle_orient(t_triangle *triangle)
{
	t_vector3	p1p2_vec;
	t_vector3	p1p3_vec;
	t_vector3	orient;

	p1p2_vec = diffvec3(&triangle->y, &triangle->x);
	p1p3_vec = diffvec3(&triangle->z, &triangle->x);
	orient = cross3(&p1p2_vec, &p1p3_vec);
	return (normvec3(&orient));
}
