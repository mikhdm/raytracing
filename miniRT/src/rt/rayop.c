#include "canvas.h"
#include "shade.h"
#include "linop.h"
#include "intersect.h"
#include "utils.h"
#include "libft.h"
#include <math.h>

double	intersect(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
			t_figure *figure)
{
	double	t;

	t = INFINITY;
	if (ft_strncmp(figure->label, LABEL_SPHERE, ft_strlen(LABEL_SPHERE)) == 0)
		t = intersect_sphere(p0, dirvec, (t_sphere *)figure->content);
	else if (ft_strncmp(figure->label, LABEL_PLANE,
			ft_strlen(LABEL_PLANE)) == 0)
		t = intersect_plane(p0, dirvec, (t_plane *)figure->content);
	else if (ft_strncmp(figure->label, LABEL_SQUARE,
			ft_strlen(LABEL_SQUARE)) == 0)
		t = intersect_square(data, p0, dirvec, (t_square *)figure->content);
	else if (ft_strncmp(figure->label, LABEL_TRIANGLE,
			ft_strlen(LABEL_TRIANGLE)) == 0)
		t = intersect_triangle(data, p0, dirvec, (t_triangle *)figure->content);
	else if (ft_strncmp(figure->label, LABEL_CYLINDER,
			ft_strlen(LABEL_CYLINDER)) == 0)
		t = intersect_cylinder(p0, dirvec, (t_cylinder *)figure->content);
	return (t);
}

t_pair_figure_double	intersect_closest(t_data *data, t_vector3 *p0,
							t_vector3 *dirvec, t_pair_double *range)
{
	double					t;
	t_pair_figure_double	pair_figure_t;
	t_figure				*curr;

	curr = data->figures;
	pair_figure_t = (t_pair_figure_double){.figure = NULL, .t = INFINITY};
	while (curr)
	{
		t = intersect(data, p0, dirvec, curr);
		if (t >= range->first && t <= range->second && t < pair_figure_t.t)
		{
			pair_figure_t.t = t;
			pair_figure_t.figure = curr;
		}
		curr = curr->next;
	}
	if (!pair_figure_t.figure)
		return ((t_pair_figure_double){.figure = NULL, .t = INFINITY});
	return (pair_figure_t);
}

int	shade(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
		t_pair_figure_double *pair_figure_t)
{
	int			color;
	t_figure	*figure;

	color = COLOR_BACKGROUND;
	figure = pair_figure_t->figure;
	if (ft_strncmp(figure->label, LABEL_SPHERE,
			ft_strlen(LABEL_SPHERE)) == 0)
		color = shade_sphere(data, p0, dirvec, pair_figure_t);
	else if (ft_strncmp(figure->label, LABEL_PLANE,
			ft_strlen(LABEL_PLANE)) == 0)
		color = shade_plane(data, p0, dirvec, pair_figure_t);
	else if (ft_strncmp(figure->label, LABEL_SQUARE,
			ft_strlen(LABEL_SQUARE)) == 0)
		color = shade_square(data, p0, dirvec, pair_figure_t);
	else if (ft_strncmp(figure->label, LABEL_TRIANGLE,
			ft_strlen(LABEL_TRIANGLE)) == 0)
		color = shade_triangle(data, p0, dirvec, pair_figure_t);
	else if (ft_strncmp(figure->label, LABEL_CYLINDER,
			ft_strlen(LABEL_CYLINDER)) == 0)
		color = shade_cylinder(data, p0, dirvec, pair_figure_t);
	return (color);
}

int	trace(t_data *data, t_vector3 *p0, t_vector3 *dirvec, t_pair_double *range)
{
	t_pair_figure_double	pair_figure_t;

	pair_figure_t = intersect_closest(data, p0, dirvec, range);
	if (isinf(pair_figure_t.t))
		return (COLOR_BACKGROUND);
	return (shade(data, p0, dirvec, &pair_figure_t));
}
