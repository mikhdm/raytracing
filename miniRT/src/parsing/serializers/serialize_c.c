#include "canvas.h"
#include "utils.h"
#include "parsing/serialize.h"
#include "parsing/errors.h"
#include "parsing/validate.h"
#include "libft.h"
#include <stddef.h>
#include <errno.h>

static void	lst_cam_append(t_camera **head, t_camera *new)
{
	t_camera	**curr;

	curr = head;
	if (!*curr)
		*curr = new;
	else
	{
		while ((*curr)->next)
			curr = &((*curr)->next);
		(*curr)->next = new;
	}
}

static void	set_point(t_data *data, char **strs, char **strs_point,
					  t_camera **cam)
{
	size_t		strslen;

	strslen = ft_strslen(strs_point);
	if (strslen != 3)
	{
		ft_strsfree(strs_point);
		serialize_error(ERROR_SYNTAX_CAMERA, 255, data, strs);
	}
	if (!valid_point3((const char **)strs_point, strslen, &((*cam)->center)))
	{
		ft_strsfree(strs_point);
		serialize_error(ERROR_INVALID_CAMERA, 255, data, strs);
	}
	ft_strsfree(strs_point);
}

static void	set_orient(t_data *data, char **strs, char **strs_orient,
					   t_camera **cam)
{
	size_t	strslen;

	strslen = ft_strslen(strs_orient);
	if (strslen != 3)
	{
		ft_strsfree(strs_orient);
		serialize_error(ERROR_SYNTAX_CAMERA, 255, data, strs);
	}
	if (!valid_orient((const char **)strs_orient, strslen, &(*cam)->orient))
	{
		ft_strsfree(strs_orient);
		serialize_error(ERROR_INVALID_CAMERA, 255, data, strs);
	}
	ft_strsfree(strs_orient);
}

static void	set_camera(t_data *data, char **strs, t_camera *cam)
{
	char		**strs_point;
	char		**strs_orient;
	char		*str_fov;

	lst_cam_append(&(data->cam), cam);
	strs_point = ft_split_any(strs[1], ',');
	if (!strs_point)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_point(data, strs, strs_point, &cam);
	strs_orient = ft_split_any(strs[2], ',');
	if (!strs_orient)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_orient(data, strs, strs_orient, &cam);
	str_fov = strs[3];
	if (!ft_isfloatable(str_fov))
		serialize_error(ERROR_INVALID_CAMERA, 255, data, strs);
	cam->fov = ft_atof(str_fov);
	if (ft_flt(cam->fov, 0) || ft_fgt(cam->fov, 180))
		serialize_error(ERROR_INVALID_CAMERA, 255, data, strs);
}

t_data	*serialize_c(t_data *data, char **strs)
{
	size_t		strslen;
	t_camera	*cam;

	strslen = ft_strslen(strs);
	if (strslen != 4)
		serialize_error(ERROR_SYNTAX_CAMERA, 255, data, strs);
	cam = NULL;
	if (!(alloca_to((void **)&cam, sizeof(t_camera))))
		serialize_error(ERROR_ERRNO, errno, data, strs);
	cam->next = NULL;
	if (!data->cam)
		cam->active = TRUE;
	else
		cam->active = FALSE;
	cam->viewport = NULL;
	set_camera(data, strs, cam);
	return (data);
}
