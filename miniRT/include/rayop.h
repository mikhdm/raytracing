#ifndef RAYOP_H
# define RAYOP_H

# include "canvas.h"
# include "linop.h"
# include "utils.h"

/*
* shade - function calculates color with light and shadows 
* 	on a figure depending on dirvec, t param, and figure. 
*/
int						shade(t_data *data,
							  t_vector3 *p0,
							  t_vector3 *dirvec,
							  t_pair_figure_double *pair_figure_t);
int						trace(t_data *data,
							  t_vector3 *p0,
							  t_vector3 *dirvec,
							  t_pair_double *range);
t_pair_figure_double	intersect_closest(t_data *data,
							t_vector3 *p0,
							t_vector3 *dirvec,
							t_pair_double *range);
double					intersect(t_data *data,
							t_vector3 *p0,
							t_vector3 *dirvec,
							t_figure *figure);
/*
* light - calculates intensity of light at point on a surface
* with orientation vector orient.
*/
int						light(t_data *data, t_vector3 *point,
							t_vector3 *orient, int scolor);
#endif
