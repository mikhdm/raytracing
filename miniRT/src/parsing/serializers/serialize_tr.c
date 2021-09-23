#include "canvas.h"
#include "utils.h"
#include "libft.h"
#include "parsing/serialize.h"
#include "parsing/errors.h"
#include <errno.h>

static void	set_point(t_data *data, char **strs, char **strs_point,
						 t_vector3 *point)
{
	if (!serialize_point(strs_point, point))
	{
		ft_strsfree(strs_point);
		serialize_error(ERROR_INVALID_TRIANGLE, 255, data, strs);
	}
	ft_strsfree(strs_point);
	strs_point = NULL;
}

static void	set_color(t_data *data, char **strs, char **strs_rgb,
						 t_triangle **triangle)
{
	int		argb;

	argb = COLOR_BACKGROUND;
	if (!serialize_rgb(strs_rgb, &argb))
	{
		ft_strsfree(strs_rgb);
		serialize_error(ERROR_INVALID_TRIANGLE, 255, data, strs);
	}
	(*triangle)->color = argb;
	ft_strsfree(strs_rgb);
	strs_rgb = NULL;
}

static void	set_figure(t_data *data, char **strs, t_triangle **triangle)
{
	t_figure	*figure;

	figure = NULL;
	if (!(alloca_to((void **)&figure, sizeof(t_figure))))
	{
		free(*triangle);
		serialize_error(ERROR_ERRNO, errno, data, strs);
	}
	figure->label = LABEL_TRIANGLE;
	figure->next = NULL;
	figure->content = *triangle;
	lst_figure_append(&data->figures, figure);
}

static void	set_triangle(t_data *data, char **strs, t_triangle *triangle)
{
	char	**strs_rgb;
	char	**strs_point;

	set_figure(data, strs, &triangle);
	strs_point = ft_split_any(strs[1], ',');
	if (!strs_point)
		serialize_error(ERROR_SYNTAX_TRIANGLE, 255, data, strs);
	set_point(data, strs, strs_point, &(triangle->x));
	strs_point = ft_split_any(strs[2], ',');
	if (!strs_point)
		serialize_error(ERROR_SYNTAX_TRIANGLE, 255, data, strs);
	set_point(data, strs, strs_point, &(triangle->y));
	strs_point = ft_split_any(strs[3], ',');
	if (!strs_point)
		serialize_error(ERROR_SYNTAX_TRIANGLE, 255, data, strs);
	set_point(data, strs, strs_point, &(triangle->z));
	strs_rgb = ft_split_any(strs[4], ',');
	if (!strs_rgb)
		serialize_error(ERROR_SYNTAX_TRIANGLE, 255, data, strs);
	set_color(data, strs, strs_rgb, &triangle);
}

t_data	*serialize_tr(t_data *data, char **strs)
{
	size_t		strslen;
	t_triangle	*triangle;

	strslen = ft_strslen(strs);
	if (strslen != 5)
		serialize_error(ERROR_SYNTAX_TRIANGLE, 255, data, strs);
	triangle = NULL;
	if (!(alloca_to((void **)&triangle, sizeof(t_triangle))))
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_triangle(data, strs, triangle);
	return (data);
}
