#include "canvas.h"
#include "linop.h"
#include "utils.h"

/*
* calc_cylinder_orient - non optimal implementation of cylinder orient vector
* lookup at point p_hit.
*/
t_vector3	calc_cylinder_orient(t_cylinder *cylinder,
				t_vector3 *p0, t_vector3 *dirvec, double t)
{
	double		m;
	t_vector3	p_hit;
	t_vector3	co;
	t_vector3	p_orient;
	t_vector3	axis_point;

	p_hit = calc_ray_point(p0, dirvec, t);
	co = diffvec3(p0, &cylinder->center);
	m = dot3(dirvec, &cylinder->orient) * t + dot3(&co, &cylinder->orient);
	axis_point = cmultvec3(m, &cylinder->orient);
	axis_point = sumvec3(&cylinder->center, &axis_point);
	p_orient = diffvec3(&p_hit, &axis_point);
	return (normvec3(&p_orient));
}
