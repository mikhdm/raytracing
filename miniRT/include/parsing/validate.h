#ifndef VALIDATE_H
# define VALIDATE_H

# include "canvas.h"
# include "linop.h"
# include <stddef.h>

short	valid_rgb(const char **strs_rgb, size_t strslen, int *argb);
short	valid_orient(const char **strs_orient, size_t strslen,
			t_vector3 *orient);
short	valid_point3(const char **strs_point, size_t strslen,
			t_vector3 *point);

#endif