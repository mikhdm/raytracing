#include "color.h"
#include "canvas.h"
#include "linop.h"
#include "rayop.h"
#include <math.h>

static int	calc_d_light(t_light *spot, t_vector3 *orient,
				t_vector3 *lightvec, int const scolor)
{
	int	color;

	color = linargb(spot->color);
	color = cmultargb(color, spot->brightness);
	color = multargb(color, scolor);
	color = cmultargb(color, fmax(0.0, dot3(orient, lightvec)));
	return (color);
}

static int	ambient_light(t_data *data, int const scolor)
{
	int	acolor;

	acolor = linargb(data->ambience->color);
	acolor = cmultargb(acolor, data->ambience->intensity);
	return (multargb(acolor, scolor));
}

static int	diffuse_light(t_data *data,
				t_vector3 *point, t_vector3 *orient, int const scolor)
{
	int						color;
	t_light					*curr;
	t_vector3				p_shadow;
	t_pair_figure_double	pair_figure_t;
	t_vector3				lightvec;

	curr = data->light;
	color = COLOR_BLACK;
	while (curr)
	{
		lightvec = diffvec3(&curr->center, point);
		p_shadow = cmultvec3(1e-4, &lightvec);
		p_shadow = sumvec3(point, &p_shadow);
		pair_figure_t = intersect_closest(data, &p_shadow, &lightvec,
				&((t_pair_double){1e-4, 1}));
		if (pair_figure_t.figure)
		{
			curr = curr->next;
			continue ;
		}
		lightvec = normvec3(&lightvec);
		color = addargb(color, calc_d_light(curr, orient, &lightvec, scolor));
		curr = curr->next;
	}
	return (color);
}

int	light(t_data *data,
		t_vector3 *point, t_vector3 *orient, int const scolor)
{
	int	ambient_color;
	int	diffuse_color;
	int	surface_color;

	surface_color = linargb(scolor);
	ambient_color = ambient_light(data, surface_color);
	diffuse_color = diffuse_light(data, point, orient, surface_color);
	return (gammargb(addargb(ambient_color, diffuse_color)));
}
