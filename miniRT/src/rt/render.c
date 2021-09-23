#include "canvas.h"
#include "linop.h"
#include "rayop.h"
#include "utils.h"

void	render(t_data *data, t_camera *cam, t_pair_double *range)
{
	int				x;
	int				y;
	int				color;
	t_vector3		dirvec;

	if (!cam)
		return ;
	y = data->screen->height / 2;
	while (y > -data->screen->height / 2)
	{
		x = -data->screen->width / 2;
		while (x < data->screen->width / 2)
		{
			dirvec = canvas_to_viewport(data, cam, x, y);
			dirvec = look_at(data, cam, &dirvec);
			color = trace(data, &cam->center, &dirvec, range);
			putpixel(data, x, y, color);
			++x;
		}
		--y;
	}
}
