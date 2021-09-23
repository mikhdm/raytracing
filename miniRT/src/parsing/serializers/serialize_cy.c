#include "canvas.h"
#include "utils.h"
#include "libft.h"
#include "parsing/errors.h"
#include "parsing/serialize.h"
#include <math.h>
#include <errno.h>

static	void	set_orient(t_data *data, char **strs, char **strs_orient,
					t_cylinder **cylinder)
{
	if (!serialize_orient(strs_orient, &(*cylinder)->orient))
	{
		ft_strsfree(strs_orient);
		serialize_error(ERROR_INVALID_CYLINDER, 255, data, strs);
	}
	ft_strsfree(strs_orient);
	strs_orient = NULL;
}

static	void	set_point(t_data *data, char **strs, char **strs_point,
					t_cylinder **cylinder)
{
	if (!serialize_point(strs_point, &(*cylinder)->center))
	{
		ft_strsfree(strs_point);
		serialize_error(ERROR_INVALID_CYLINDER, 255, data, strs);
	}
	ft_strsfree(strs_point);
	strs_point = NULL;
}

static	void	set_figure(t_data *data, char **strs, t_cylinder **cylinder)
{
	t_figure	*figure;

	figure = NULL;
	if (!(alloca_to((void **)&figure, sizeof(t_figure))))
	{
		free(*cylinder);
		serialize_error(ERROR_ERRNO, errno, data, strs);
	}
	figure->label = LABEL_CYLINDER;
	figure->next = NULL;
	figure->content = *cylinder;
	lst_figure_append(&data->figures, figure);
}

static	void	set_cylinder(t_data *data, char **strs, t_cylinder *cylinder)
{
	char	**strs_point;
	char	**strs_orient;
	char	**strs_rgb;

	set_figure(data, strs, &cylinder);
	strs_point = ft_split_any(strs[1], ',');
	if (!strs_point)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_point(data, strs, strs_point, &cylinder);
	strs_orient = ft_split_any(strs[2], ',');
	if (!strs_orient)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_orient(data, strs, strs_orient, &cylinder);
	if (!ft_isfloatable(strs[3]) || !ft_isfloatable(strs[4]))
		serialize_error(ERROR_SYNTAX_CYLINDER, 255, data, strs);
	cylinder->diameter = ft_atof(strs[3]);
	cylinder->height = ft_atof(strs[4]);
	if (ft_flt(cylinder->diameter, 1e-10) || ft_flt(cylinder->height, 1e-10)
		|| isinf(cylinder->diameter) || isnan(cylinder->diameter)
		|| isinf(cylinder->height) || isinf(cylinder->height))
		serialize_error(ERROR_INVALID_CYLINDER, 255, data, strs);
	strs_rgb = ft_split_any(strs[5], ',');
	if (!strs_rgb)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	serialize_cy_rgb(data, strs, strs_rgb, &cylinder);
}

t_data	*serialize_cy(t_data *data, char **strs)
{
	size_t		strslen;
	t_cylinder	*cylinder;

	strslen = ft_strslen(strs);
	if (strslen != 6)
		serialize_error(ERROR_SYNTAX_CYLINDER, 255, data, strs);
	cylinder = NULL;
	if (!(alloca_to((void **)&cylinder, sizeof(t_cylinder))))
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_cylinder(data, strs, cylinder);
	return (data);
}
