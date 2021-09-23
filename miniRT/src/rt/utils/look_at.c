#include "canvas.h"
#include "linop.h"
#include "parsing/errors.h"
#include <stdlib.h>
#include <errno.h>

static void	free_rot_matrix(double **rot, size_t sz)
{
	size_t	i;	

	i = 0;
	while (i < sz)
		free(rot[i++]);
	free(rot);
}

static double	**build_rot_matrix(t_data *data)
{
	double	**rot;
	size_t	size;
	size_t	i;

	size = 3;
	i = 0;
	rot = malloc(sizeof(double *) * size);
	if (!rot)
		ft_pexitfree(ERROR_ERRNO, errno, data);
	while (i < size)
	{
		rot[i] = malloc(sizeof(double) * size);
		if (!rot[i])
		{
			free_rot_matrix(rot, i);
			ft_pexitfree(ERROR_ERRNO, errno, data);
		}
		++i;
	}
	return (rot);
}

static double	**get_rot_matrix(t_data *data, t_vector3 *right, t_vector3 *up,
					t_vector3 *forward)
{
	double	**rot;

	rot = build_rot_matrix(data);
	rot[0][0] = right->x;
	rot[1][0] = right->y;
	rot[2][0] = right->z;
	rot[0][1] = up->x;
	rot[1][1] = up->y;
	rot[2][1] = up->z;
	rot[0][2] = forward->x;
	rot[1][2] = forward->y;
	rot[2][2] = forward->z;
	return (rot);
}

t_vector3	look_at(t_data *data, t_camera *cam, t_vector3 *dirvec)
{
	t_vector3	tmp;
	t_vector3	right;
	t_vector3	up;
	t_vector3	rotdir;
	double		**rot;

	tmp = (t_vector3){.x = 0, .y = 100, .z = 0};
	if (!iscollinvec3(&tmp, &(cam->orient)))
	{
		right = cross3(&tmp, &(cam->orient));
		up = cross3(&(cam->orient), &right);
	}
	else
	{
		tmp = (t_vector3){.x = 100, .y = 0, .z = 0};
		up = cross3(&(cam->orient), &tmp);
		right = cross3(&up, &(cam->orient));
	}
	up = normvec3(&up);
	right = normvec3(&right);
	rot = get_rot_matrix(data, &right, &up, &(cam->orient));
	rotdir = mat33multvec3(rot, dirvec);
	rotdir = normvec3(&rotdir);
	free_rot_matrix(rot, 3);
	return (rotdir);
}
