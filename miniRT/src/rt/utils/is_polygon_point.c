#include "linop.h"
#include "utils.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

static t_vector3	*crosses(t_vector3 *p_vertex_vecs, size_t size)
{
	size_t		i;
	t_vector3	*vecs;

	if (!alloca_to((void **)&vecs, sizeof(t_vector3) * size))
		return (NULL);
	i = 0;
	while (i < size)
	{
		vecs[i] = cross3(&p_vertex_vecs[i], &p_vertex_vecs[(i + 1) % size]);
		++i;
	}
	return (vecs);
}

static short	signcheck(double *checks, size_t size)
{
	size_t		i;
	short		sign;
	short		flag;

	i = 0;
	flag = TRUE;
	sign = signbit(checks[i++]);
	if (sign)
	{
		while (i < size)
			if (!signbit(checks[i++]))
				flag = FALSE;
	}
	else
		while (i < size)
			if (signbit(checks[i++]))
				flag = FALSE;
	return (flag);
}

static short	pointcheck(t_vector3 *cross_vecs,
					size_t size, t_vector3 *orient)
{
	double			*checks;
	size_t			i;
	t_vector3		diffvec;
	short int		flag;

	i = 0;
	flag = TRUE;
	checks = malloc(sizeof(double) * size);
	if (!checks)
		return (-1);
	while (i < size)
	{
		diffvec = diffvec3(&cross_vecs[i], orient);
		checks[i] = dot3(&cross_vecs[i], orient) / hypotvec3(&diffvec);
		++i;
	}
	flag = signcheck(checks, size);
	free(checks);
	return (flag);
}

static int	clean_memory(t_vector3 *p_vertex_vecs, t_vector3 *cross_vecs,
				int retval)
{
	if (p_vertex_vecs)
		free(p_vertex_vecs);
	if (cross_vecs)
		free(cross_vecs);
	return (retval);
}

short int	is_polygon_point(t_vector3 *p_hit,
				t_vector3 *vertices, t_vector3 *orient, size_t size)
{
	t_vector3	*p_vertex_vecs;
	t_vector3	*cross_vecs;
	size_t		i;
	short int	check;

	check = FALSE;
	if (!alloca_to((void **)&p_vertex_vecs, sizeof(t_vector3) * size))
		return (-1);
	i = 0;
	while (i < size)
	{
		p_vertex_vecs[i] = diffvec3(&vertices[i], p_hit);
		++i;
	}
	cross_vecs = crosses(p_vertex_vecs, size);
	if (!cross_vecs)
		return (clean_memory(p_vertex_vecs, NULL, -1));
	check = pointcheck(cross_vecs, size, orient);
	if (check == -1)
		return (clean_memory(p_vertex_vecs, cross_vecs, -1));
	free(p_vertex_vecs);
	free(cross_vecs);
	return (check);
}
