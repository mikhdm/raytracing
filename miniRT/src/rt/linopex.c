#include "linop.h"
#include "libft.h"
#include <math.h>

double	hypotvec3(t_vector3 *vec)
{
	return (pow(dot3(vec, vec), 0.5));
}

t_vector3	normvec3(t_vector3 *vec)
{
	double	length;

	length = hypotvec3(vec);
	return (cmultvec3(pow(length, -1), vec));
}

short int	iscollinvec3(t_vector3 *left, t_vector3 *right)
{
	short int	collinear;
	t_vector3	crossvec;

	collinear = FALSE;
	crossvec = cross3(left, right);
	if (ft_fequal(crossvec.x, 0)
		&& ft_fequal(crossvec.y, 0)
		&& ft_fequal(crossvec.z, 0))
		collinear = TRUE;
	return (collinear);
}

t_vector3	mat33multvec3(double *mat[3], t_vector3 *vec)
{
	double	tmp[3];

	tmp[0] = vec->x * mat[0][0] + vec->y * mat[0][1] + vec->z * mat[0][2];
	tmp[1] = vec->x * mat[1][0] + vec->y * mat[1][1] + vec->z * mat[1][2];
	tmp[2] = vec->x * mat[2][0] + vec->y * mat[2][1] + vec->z * mat[2][2];
	return ((t_vector3){.x = tmp[0], .y = tmp[1], .z = tmp[2]});
}
