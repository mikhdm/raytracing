#include "canvas.h"
#include "utils.h"
#include "parsing/errors.h"
#include "parsing/serialize.h"
#include "libft.h"
#include <stddef.h>
#include <errno.h>

static	void	set_orient(t_data *data, char **strs, char **strs_orient,
					t_plane **plane)
{
	if (!serialize_orient(strs_orient, &(*plane)->orient))
	{
		ft_strsfree(strs_orient);
		serialize_error(ERROR_INVALID_PLANE, 255, data, strs);
	}
	ft_strsfree(strs_orient);
	strs_orient = NULL;
}

static	void	set_point(t_data *data, char **strs, char **strs_point,
					t_plane **plane)
{
	if (!serialize_point(strs_point, &(*plane)->center))
	{
		ft_strsfree(strs_point);
		serialize_error(ERROR_INVALID_PLANE, 255, data, strs);
	}
	ft_strsfree(strs_point);
	strs_point = NULL;
}

static	void	set_figure(t_data *data, char **strs, t_plane **plane)
{
	t_figure	*figure;

	figure = NULL;
	if (!(alloca_to((void **)&figure, sizeof(t_figure))))
	{
		free(*plane);
		serialize_error(ERROR_ERRNO, errno, data, strs);
	}
	figure->label = LABEL_PLANE;
	figure->next = NULL;
	figure->content = *plane;
	lst_figure_append(&data->figures, figure);
}

static	void	set_plane(t_data *data, char **strs, t_plane *plane)
{
	char	**strs_point;
	char	**strs_orient;
	char	**strs_rgb;

	set_figure(data, strs, &plane);
	strs_point = ft_split_any(strs[1], ',');
	if (!strs_point)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_point(data, strs, strs_point, &plane);
	strs_orient = ft_split_any(strs[2], ',');
	if (!strs_orient)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_orient(data, strs, strs_orient, &plane);
	strs_rgb = ft_split_any(strs[3], ',');
	if (!strs_rgb)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	serialize_pl_rgb(data, strs, strs_rgb, &plane);
}

t_data	*serialize_pl(t_data *data, char **strs)
{
	size_t	strslen;
	t_plane	*plane;

	strslen = ft_strslen(strs);
	if (strslen != 4)
		serialize_error(ERROR_SYNTAX_PLANE, 255, data, strs);
	plane = NULL;
	if (!(alloca_to((void **)&plane, sizeof(t_plane))))
		serialize_error(ERROR_SYNTAX_PLANE, 255, data, strs);
	set_plane(data, strs, plane);
	return (data);
}
