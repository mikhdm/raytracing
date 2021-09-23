#include "linop.h"
#include "libft.h"
#include <math.h>

double	dot3(t_vector3 *left, t_vector3 *right)
{
	double	x;
	double	y;
	double	z;

	x = left->x * right->x;
	y = left->y * right->y;
	z = left->z * right->z;
	return (x + y + z);
}

t_vector3	cross3(t_vector3 *left, t_vector3 *right)
{
	t_vector3	crossvec;

	crossvec = (t_vector3){.x = .0, .y = .0, .z = .0};
	crossvec.x = fma(left->y, right->z, -left->z * right->y);
	crossvec.y = fma(right->x, left->z, -left->x * right->z);
	crossvec.z = fma(left->x, right->y, -right->x * left->y);
	return (crossvec);
}

t_vector3	diffvec3(t_vector3 *left, t_vector3 *right)
{
	t_vector3	diffvec;

	diffvec = (t_vector3){.x = .0, .y = .0, .z = .0};
	diffvec.x = left->x - right->x;
	diffvec.y = left->y - right->y;
	diffvec.z = left->z - right->z;
	return (diffvec);
}

t_vector3	sumvec3(t_vector3 *left, t_vector3 *right)
{
	t_vector3	sumvec;

	sumvec = (t_vector3){.x = .0, .y = .0, .z = .0};
	sumvec.x = left->x + right->x;
	sumvec.y = left->y + right->y;
	sumvec.z = left->z + right->z;
	return (sumvec);
}

t_vector3	cmultvec3(double const value, t_vector3 *vector)
{
	t_vector3	cmultvec;

	cmultvec.x = value * vector->x;
	cmultvec.y = value * vector->y;
	cmultvec.z = value * vector->z;
	return (cmultvec);
}
