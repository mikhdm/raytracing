#include "canvas.h"
#include "linop.h"
#include "utils.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <errno.h>

static t_vector3	get_dirvec(t_vector3 *viewpoint)
{
	t_vector3	basis[3];
	t_vector3	xu;
	t_vector3	yv;
	t_vector3	dw;
	t_vector3	dirvec;

	basis[0] = (t_vector3){1, 0, 0};
	basis[1] = (t_vector3){0, 1, 0};
	basis[2] = (t_vector3){0, 0, -1};
	xu = cmultvec3(viewpoint->x, &basis[0]);
	yv = cmultvec3(viewpoint->y, &basis[1]);
	dw = cmultvec3(viewpoint->z, &basis[2]);
	dirvec = sumvec3(&xu, &yv);
	dirvec = sumvec3(&dirvec, &dw);
	return (dirvec);
}

t_viewport	calc_viewport(t_data *data, t_camera *cam)
{
	t_viewport	viewport;
	double		fov;

	fov = cam->fov;
	if (ft_fequal(cam->fov, 180))
		fov -= 1e-2;
	viewport.width = 2 * tan(deg_to_rad(fov / 2));
	viewport.height = data->screen->height
		* (viewport.width / (double)data->screen->width);
	return (viewport);
}

/*
*
* canvas_to_viewport - camera position independent ray direction calc.
*
*/
t_vector3	canvas_to_viewport(t_data *data, t_camera *cam, int x, int y)
{
	t_vector3	dirvec;
	t_vector3	viewpoint;

	viewpoint.x = (cam->viewport->width / (double)data->screen->width)
		* (x + 0.5);
	viewpoint.y = (cam->viewport->height / (double)data->screen->height)
		* (y + 0.5);
	viewpoint.z = -1;
	dirvec = get_dirvec(&viewpoint);
	return (normvec3(&dirvec));
}

void	init(t_data *data, short windowed)
{
	data->mlx = mlx_init();
	data->img = mlx_new_image(
			data->mlx,
			data->screen->width,
			data->screen->height);
	data->addr = mlx_get_data_addr(
			data->img,
			&data->bpp,
			&data->length,
			&data->endian);
	if (windowed)
		data->window = mlx_new_window(
				data->mlx,
				data->screen->width,
				data->screen->height,
				data->screen->title);
}

void	putpixel(t_data *data, int x, int y, int color)
{
	char	*dest;
	int		screen_x;
	int		screen_y;

	screen_x = data->screen->width / 2 + x;
	screen_y = data->screen->height / 2 - y;
	dest = (data->addr
			+ (screen_y * data->length + screen_x * (data->bpp / 8)));
	*(unsigned int *)dest = color;
}
