#include "canvas.h"
#include "utils.h"
#include <stddef.h>

static t_camera	*get_last(t_data *data)
{
	t_camera	*curr;

	curr = data->cam;
	if (!curr)
		return (NULL);
	while (curr->next)
		curr = curr->next;
	return (curr);
}

static t_camera	*get_active_cam(t_data *data, t_camera **prev)
{
	t_camera	*cam;

	cam = data->cam;
	*prev = data->cam;
	while (cam)
	{
		if (cam->active)
			break ;
		*prev = cam;
		cam = cam->next;
	}
	return (cam);
}

t_camera	*get_cam(t_data *data, short position)
{
	t_camera	*cam;
	t_camera	*prev;

	if (!data->cam)
		return (NULL);
	cam = get_active_cam(data, &prev);
	cam->active = FALSE;
	if (position == POS_CAM_NEXT)
	{
		cam = cam->next;
		if (!cam)
			cam = data->cam;
	}
	if (position == POS_CAM_PREV)
	{
		if (cam == data->cam)
			cam = get_last(data);
		else
			cam = prev;
	}
	cam->active = TRUE;
	return (cam);
}
