#include "canvas.h"
#include "mlx.h"
#include <unistd.h>

static	void	clean_lights(t_data *data)
{
	t_light	*curr;
	t_light	*freeable;

	curr = data->light;
	freeable = data->light;
	while (curr)
	{
		curr = curr->next;
		free(freeable);
		freeable = curr;
	}
}

static	void	clean_cameras(t_data *data)
{
	t_camera	*curr;
	t_camera	*freeable;

	curr = data->cam;
	freeable = data->cam;
	while (curr)
	{
		curr = curr->next;
		free(freeable->viewport);
		free(freeable);
		freeable = curr;
	}
}

static	void	clean_figures(t_data *data)
{
	t_figure	*curr;
	t_figure	*freeable;

	curr = data->figures;
	freeable = data->figures;
	while (curr)
	{
		curr = curr->next;
		free(freeable->content);
		free(freeable);
		freeable = curr;
	}
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	if (data->screen)
		free(data->screen);
	if (data->ambience)
		free(data->ambience);
	if (data->light)
		clean_lights(data);
	if (data->cam)
		clean_cameras(data);
	if (data->figures)
		clean_figures(data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->fildes != -1)
		close(data->fildes);
	free(data);
}
