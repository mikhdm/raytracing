#include "canvas.h"
#include "utils.h"
#include "parsing/serialize.h"
#include "parsing/errors.h"
#include "libft.h"
#include <stddef.h>
#include <errno.h>

static	void	lst_light_append(t_light **head, t_light *new)
{
	t_light	**curr;

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

static	void	set_color(t_data *data, char **strs, char **strs_rgb,
					t_light **light)
{
	int	argb;

	argb = COLOR_BACKGROUND;
	if (!serialize_rgb(strs_rgb, &argb))
	{
		ft_strsfree(strs_rgb);
		serialize_error(ERROR_INVALID_LIGHT, 255, data, strs);
	}
	(*light)->color = argb;
	ft_strsfree(strs_rgb);
	strs_rgb = NULL;
}

static	void	set_point(t_data *data, char **strs, char **strs_point,
					t_light **light)
{
	if (!serialize_point(strs_point, &(*light)->center))
	{
		ft_strsfree(strs_point);
		serialize_error(ERROR_INVALID_LIGHT, 255, data, strs);
	}
	ft_strsfree(strs_point);
	strs_point = NULL;
}

static	void	set_light(t_data *data, char **strs, t_light *light)
{
	char	**strs_point;
	char	**strs_color;

	lst_light_append(&(data->light), light);
	strs_point = ft_split_any(strs[1], ',');
	if (!strs_point)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_point(data, strs, strs_point, &light);
	if (!ft_isfloatable(strs[2]))
		serialize_error(ERROR_INVALID_LIGHT, 255, data, strs);
	light->brightness = ft_atof(strs[2]);
	if (ft_flt(light->brightness, 0) || ft_fgt(light->brightness, 1))
		serialize_error(ERROR_INVALID_LIGHT, 255, data, strs);
	strs_color = ft_split_any(strs[3], ',');
	if (!strs_color)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_color(data, strs, strs_color, &light);
}

t_data	*serialize_l(t_data *data, char **strs)
{
	size_t	strslen;
	t_light	*light;

	strslen = ft_strslen(strs);
	if (strslen != 4)
		serialize_error(ERROR_SYNTAX_LIGHT, 255, data, strs);
	light = NULL;
	if (!(alloca_to((void **)&light, sizeof(t_light))))
		serialize_error(ERROR_ERRNO, errno, data, strs);
	light->next = NULL;
	set_light(data, strs, light);
	return (data);
}
