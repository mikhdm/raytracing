#include "canvas.h"
#include "linop.h"
#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

static void	set_square_vectors(t_square *square, t_vector3 *sq_vecs)
{
	t_vector3	rand_vec;

	rand_vec = (t_vector3){.x = 1000, .y = 0, .z = 0};
	if (iscollinvec3(&rand_vec, &square->orient))
		rand_vec = (t_vector3){.x = 0, .y = 1000, .z = 0};
	sq_vecs[0] = cross3(&rand_vec, &square->orient);
	sq_vecs[1] = cross3(&sq_vecs[0], &square->orient);
	sq_vecs[0] = normvec3(&sq_vecs[0]);
	sq_vecs[1] = normvec3(&sq_vecs[1]);
	sq_vecs[2] = cmultvec3(-1.0, &sq_vecs[0]);
	sq_vecs[3] = cmultvec3(-1.0, &sq_vecs[1]);
}

t_vector3	*gen_square_vertices(t_square *square)
{
	t_vector3	*vertices;
	t_vector3	sq_vecs[4];
	size_t		i;

	vertices = NULL;
	if (!alloca_to((void **)&vertices, sizeof(t_vector3) * 4))
		return (NULL);
	set_square_vectors(square, sq_vecs);
	i = 0;
	while (i < 4)
	{
		sq_vecs[i] = cmultvec3(square->size * pow(2, -0.5), &sq_vecs[i]);
		vertices[i] = sumvec3(&sq_vecs[i], &square->center);
		++i;
	}
	return (vertices);
}
