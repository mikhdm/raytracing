#include "canvas.h"
#include "linop.h"
#include "rayop.h"
#include "utils.h"

int	shade_sphere(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
		t_pair_figure_double *pair_figure_t)
{
	int			color;
	t_vector3	p_hit;
	t_vector3	orient;
	t_sphere	*sphere;

	sphere = (t_sphere *)pair_figure_t->figure->content;
	color = sphere->color;
	p_hit = calc_ray_point(p0, dirvec, pair_figure_t->t);
	orient = calc_sphere_orient(&p_hit, sphere);
	orient = calc_faceted_orient(dirvec, &orient);
	return (light(data, &p_hit, &orient, color));
}

int	shade_plane(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
		t_pair_figure_double *pair_figure_t)
{
	int			color;
	t_vector3	p_hit;
	t_plane		*plane;
	t_vector3	orient;

	plane = (t_plane *)pair_figure_t->figure->content;
	color = plane->color;
	p_hit = calc_ray_point(p0, dirvec, pair_figure_t->t);
	orient = calc_faceted_orient(dirvec, &plane->orient);
	return (light(data, &p_hit, &orient, color));
}

int	shade_square(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
		t_pair_figure_double *pair_figure_t)
{
	int			color;
	t_vector3	p_hit;
	t_square	*square;
	t_vector3	orient;

	square = (t_square *)pair_figure_t->figure->content;
	color = square->color;
	p_hit = calc_ray_point(p0, dirvec, pair_figure_t->t);
	orient = calc_faceted_orient(dirvec, &(square->orient));
	return (light(data, &p_hit, &orient, color));
}

int	shade_triangle(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
		t_pair_figure_double *pair_figure_t)
{
	int			color;
	t_vector3	p_hit;
	t_vector3	orient;
	t_triangle	*triangle;

	triangle = (t_triangle *)pair_figure_t->figure->content;
	color = triangle->color;
	p_hit = calc_ray_point(p0, dirvec, pair_figure_t->t);
	orient = calc_triangle_orient(triangle);
	orient = calc_faceted_orient(dirvec, &orient);
	return (light(data, &p_hit, &orient, color));
}

int	shade_cylinder(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
		t_pair_figure_double *pair_figure_t)
{
	int			color;
	t_vector3	p_hit;
	t_vector3	orient;
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)pair_figure_t->figure->content;
	color = cylinder->color;
	p_hit = calc_ray_point(p0, dirvec, pair_figure_t->t);
	orient = calc_cylinder_orient(cylinder, p0, dirvec, pair_figure_t->t);
	orient = calc_faceted_orient(dirvec, &orient);
	return (light(data, &p_hit, &orient, color));
}
