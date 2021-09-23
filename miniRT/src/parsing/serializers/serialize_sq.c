#include "canvas.h"
#include "libft.h"
#include "utils.h"
#include "parsing/errors.h"
#include "parsing/serialize.h"
#include <math.h>
#include <errno.h>

static void	set_orient(t_data *data, char **strs, char **strs_orient,
						  t_square **square)
{
	if (!serialize_orient(strs_orient, &(*square)->orient))
	{
		ft_strsfree(strs_orient);
		serialize_error(ERROR_INVALID_SQUARE, 255, data, strs);
	}
	ft_strsfree(strs_orient);
	strs_orient = NULL;
}

static void	set_point(t_data *data, char **strs, char **strs_point,
						 t_square **square)
{
	if (!serialize_point(strs_point, &(*square)->center))
	{
		ft_strsfree(strs_point);
		serialize_error(ERROR_INVALID_SQUARE, 255, data, strs);
	}
	ft_strsfree(strs_point);
	strs_point = NULL;
}

static void	set_figure(t_data *data, char **strs, t_square **square)
{
	t_figure	*figure;

	figure = NULL;
	if (!(alloca_to((void **)&figure, sizeof(t_figure))))
	{
		free(*square);
		serialize_error(ERROR_ERRNO, errno, data, strs);
	}
	figure->label = LABEL_SQUARE;
	figure->next = NULL;
	figure->content = *square;
	lst_figure_append(&data->figures, figure);
}

static	void	set_square(t_data *data, char **strs, t_square *square)
{
	char	**strs_point;
	char	**strs_orient;
	char	**strs_rgb;

	set_figure(data, strs, &square);
	strs_point = ft_split_any(strs[1], ',');
	if (!strs_point)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_point(data, strs, strs_point, &square);
	strs_orient = ft_split_any(strs[2], ',');
	if (!strs_orient)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_orient(data, strs, strs_orient, &square);
	if (!ft_isfloatable(strs[3]))
		serialize_error(ERROR_SYNTAX_SQUARE, 255, data, strs);
	square->size = ft_atof(strs[3]);
	if (ft_flt(square->size, 1e-10)
		|| isnan(square->size) || isinf(square->size))
		serialize_error(ERROR_INVALID_SQUARE, 255, data, strs);
	strs_rgb = ft_split_any(strs[4], ',');
	if (!strs_rgb)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	serialize_sq_rgb(data, strs, strs_rgb, &square);
}

t_data	*serialize_sq(t_data *data, char **strs)
{
	size_t		strslen;
	t_square	*square;

	strslen = ft_strslen(strs);
	if (strslen != 5)
		serialize_error(ERROR_SYNTAX_SQUARE, 255, data, strs);
	square = NULL;
	if (!(alloca_to((void **)&square, sizeof(t_square))))
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_square(data, strs, square);
	return (data);
}
