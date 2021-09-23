#ifndef SERIALIZE_H
# define SERIALIZE_H

# include "canvas.h"
# include "linop.h"

typedef t_data *(*t_serialize_func)(t_data *, char **);

t_data		*serialize(t_data *data, char *line, char **initial);
void		serialize_error(int code, int status, t_data *data, char **strs);
t_data		*serialize_r(t_data *data, char **strs);
t_data		*serialize_a(t_data *data, char **strs);
t_data		*serialize_c(t_data *data, char **strs);
t_data		*serialize_l(t_data *data, char **strs);
t_data		*serialize_sp(t_data *data, char **strs);
t_data		*serialize_cy(t_data *data, char **strs);
t_data		*serialize_pl(t_data *data, char **strs);
t_data		*serialize_tr(t_data *data, char **strs);
t_data		*serialize_sq(t_data *data, char **strs);
int			*serialize_rgb(char **strs_rgb, int *argb);
void		lst_figure_append(t_figure **head, t_figure *new);
void		serialize_cy_rgb(t_data *data, char **strs, char **strs_rgb,
				t_cylinder **cylinder);
void		serialize_sq_rgb(t_data *data, char **strs, char **strs_rgb,
				t_square **square);
void		serialize_pl_rgb(t_data *data, char **strs, char **strs_rgb,
				t_plane **plane);
t_vector3	*serialize_point(char **strs_point, t_vector3 *point);
t_vector3	*serialize_orient(char **strs_orient, t_vector3 *orient);

#endif