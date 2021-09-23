#include "event.h"
#include "canvas.h"
#include "render.h"
#include "utils.h"
#include "parsing/cleanup.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

static int	hook_close(int keycode, t_data *data)
{
	(void) keycode;
	(void) data;
	exit(0);
}

static int	hook_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		cleanup(data);
		exit(0);
	}
	else if (keycode == KEY_LEFT)
	{
		mlx_reset_image(data);
		render(data, get_cam(data, POS_CAM_PREV),
			   &(t_pair_double){.first = 1.0, .second = INFINITY});
		mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
	}
	else if (keycode == KEY_RIGHT)
	{
		mlx_reset_image(data);
		render(data, get_cam(data, POS_CAM_NEXT),
			&(t_pair_double){.first = 1.0, .second = INFINITY});
		mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
	}
	return (keycode);
}

void	bind_hooks(t_data *data)
{
	mlx_hook(data->window,
		X11_DESTROY_NOTIFY, MASK_NO_EVENT, &hook_close, data);
	mlx_hook(data->window,
		X11_KEY_PRESS, MASK_NO_EVENT, &hook_keypress, data);
}
