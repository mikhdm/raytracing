#include "canvas.h"
#include "utils.h"
#include "libft.h"
#include "parsing/errors.h"
#include "parsing/serialize.h"
#include <math.h>
#include <errno.h>

static	void	set_color(t_data *data, char **strs, char **strs_rgb,
					t_sphere **sphere)
{
	int	argb;

	argb = COLOR_BACKGROUND;
	if (!serialize_rgb(strs_rgb, &argb))
	{
		ft_strsfree(strs_rgb);
		serialize_error(ERROR_INVALID_SPHERE, 255, data, strs);
	}
	(*sphere)->color = argb;
	ft_strsfree(strs_rgb);
	strs_rgb = NULL;
}

static	void	set_point(t_data *data, char **strs, char **strs_point,
					t_sphere **sphere)
{
	if (!serialize_point(strs_point, &(*sphere)->center))
	{
		ft_strsfree(strs_point);
		serialize_error(ERROR_INVALID_SPHERE, 255, data, strs);
	}
	ft_strsfree(strs_point);
	strs_point = NULL;
}

static	void	set_figure(t_data *data, char **strs, t_sphere **sphere)
{
	t_figure	*figure;

	figure = NULL;
	if (!(alloca_to((void **)&figure, sizeof(t_figure))))
	{
		free(*sphere);
		serialize_error(ERROR_ERRNO, errno, data, strs);
	}
	figure->label = LABEL_SPHERE;
	figure->next = NULL;
	figure->content = *sphere;
	lst_figure_append(&data->figures, figure);
}

static	void	set_sphere(t_data *data, char **strs, t_sphere *sphere)
{
	char		**strs_point;
	char		**strs_rgb;

	set_figure(data, strs, &sphere);
	strs_point = ft_split_any(strs[1], ',');
	if (!strs_point)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_point(data, strs, strs_point, &sphere);
	if (!ft_isfloatable(strs[2]))
		serialize_error(ERROR_SYNTAX_SPHERE, 255, data, strs);
	sphere->diameter = ft_atof(strs[2]);
	if (ft_flt(sphere->diameter, 1e-10) || isinf(sphere->diameter)
		|| isnan(sphere->diameter))
		serialize_error(ERROR_INVALID_SPHERE, 255, data, strs);
	strs_rgb = ft_split_any(strs[3], ',');
	if (!strs_rgb)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_color(data, strs, strs_rgb, &sphere);
}

t_data	*serialize_sp(t_data *data, char **strs)
{
	size_t		strslen;
	t_sphere	*sphere;

	strslen = ft_strslen(strs);
	if (strslen != 4)
		serialize_error(ERROR_SYNTAX_SPHERE, 255, data, strs);
	sphere = NULL;
	if (!(alloca_to((void **)&sphere, sizeof(t_sphere))))
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_sphere(data, strs, sphere);
	return (data);
}
