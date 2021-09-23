#ifndef INTERSECT_H
# define INTERSECT_H

# include "canvas.h"
# include "linop.h"
# include "utils.h"

double	intersect_plane(t_vector3 *p0, t_vector3 *dirvec, t_plane *plane);
double	intersect_triangle(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
			t_triangle *triangle);
double	intersect_square(t_data *data, t_vector3 *p0, t_vector3 *dirvec,
			t_square *square);
double	intersect_sphere(t_vector3 *p0, t_vector3 *dirvec, t_sphere *sphere);
double	intersect_cylinder(t_vector3 *p0, t_vector3 *dirvec,
			t_cylinder *cylinder);

#endif 
