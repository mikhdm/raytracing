#include "canvas.h"
#include "linop.h"

t_vector3	calc_ray_point(t_vector3 *p0, t_vector3 *dirvec, double t)
{
	t_vector3	t_mult_dirvec;
	t_vector3	point;

	t_mult_dirvec = cmultvec3(t, dirvec);
	point = sumvec3(p0, &t_mult_dirvec);
	return (point);
}
