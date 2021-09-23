#include "canvas.h"
#include "linop.h"
#include "utils.h"
#include "parsing/errors.h"
#include "libft.h"
#include <math.h>
#include <errno.h>

double	intersect_plane(t_vector3 *p0, t_vector3 *dirvec, t_plane *plane)
{
	double	t;

	t = intersected_planar(p0, dirvec, &plane->center, &plane->orient);
	if (isinf(t))
		return (INFINITY);
	return (t);
}

double	intersect_square(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
			t_square *square)
{
	double		t;
	t_vector3	p_hit;
	t_vector3	*vertices;
	double		check;

	vertices = NULL;
	check = FALSE;
	t = intersected_planar(p0, dirvec, &square->center, &square->orient);
	if (isinf(t))
		return (INFINITY);
	p_hit = calc_ray_point(p0, dirvec, t);
	vertices = gen_square_vertices(square);
	if (!vertices)
		ft_pexitfree(ERROR_ERRNO, errno, data);
	check = is_polygon_point(&p_hit, vertices, &square->orient, 4);
	free(vertices);
	if (check == -1)
		ft_pexitfree(ERROR_ERRNO, errno, data);
	if (check)
		return (t);
	return (INFINITY);
}

double	intersect_triangle(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
			t_triangle *triangle)
{
	double		t;
	t_vector3	p_hit;
	short		check;
	t_vector3	orient;
	t_vector3	centroid;

	orient = calc_triangle_orient(triangle);
	centroid.x = (triangle->x.x + triangle->y.x + triangle->z.x) / 3.0;
	centroid.y = (triangle->x.y + triangle->y.y + triangle->z.y) / 3.0;
	centroid.z = (triangle->x.z + triangle->y.z + triangle->z.z) / 3.0;
	t = intersected_planar(p0, dirvec, &centroid, &orient);
	if (isinf(t))
		return (INFINITY);
	p_hit = calc_ray_point(p0, dirvec, t);
	check = is_polygon_point(&p_hit,
			(t_vector3[]){triangle->x, triangle->y, triangle->z},
			&orient, 3);
	if (check == -1)
		ft_pexitfree(ERROR_ERRNO, errno, data);
	if (check)
		return (t);
	return (INFINITY);
}

double	intersect_sphere(t_vector3 *p0, t_vector3 *dirvec, t_sphere *sphere)
{
	double			radius;
	t_vector3		co;
	t_pair_double	values;

	radius = sphere->diameter / 2;
	co = diffvec3(p0, &sphere->center);
	values = calc_quad_equation(
			dot3(dirvec, dirvec),
			2 * dot3(dirvec, &co),
			dot3(&co, &co) - pow(radius, 2));
	return (calc_min_t(values));
}

double	intersect_cylinder(t_vector3 *p0, t_vector3 *dirvec,
			t_cylinder *cylinder)
{
	double			radius;
	t_vector3		co;
	t_pair_double	values_t;

	radius = cylinder->diameter / 2;
	co = diffvec3(p0, &cylinder->center);
	values_t = calc_quad_equation(
			(dot3(dirvec, dirvec)
				- pow(dot3(&cylinder->orient, dirvec), 2.0)),
			2 * (dot3(&co, dirvec)
				- (dot3(dirvec, &cylinder->orient)
					* dot3(&co, &cylinder->orient))),
			(dot3(&co, &co)
				- pow(dot3(&co, &cylinder->orient), 2.0) - pow(radius, 2.0)));
	return (calc_cylinder_min_t(p0, &values_t, dirvec, cylinder));
}
