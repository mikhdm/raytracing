#include "canvas.h"
#include "libft.h"
#include "utils.h"
#include "parsing/errors.h"
#include "parsing/serialize.h"
#include "parsing/validate.h"
#include <errno.h>

static void	set_color(t_data *data, char **strs, char **strsrgb)
{
	size_t	strslen;
	int		argb;

	argb = COLOR_BACKGROUND;
	strslen = ft_strslen(strsrgb);
	if (strslen != 3)
	{
		ft_strsfree(strsrgb);
		serialize_error(ERROR_SYNTAX_AMBIENCE, 255, data, strs);
	}
	if (!valid_rgb((const char **)strsrgb, strslen, &argb))
	{
		ft_strsfree(strsrgb);
		serialize_error(ERROR_INVALID_AMBIENCE, 255, data, strs);
	}
	data->ambience->color = argb;
}

static void	set_ambience(t_data *data, char **strs)
{
	size_t		strslen;
	char		**strsrgb;

	strslen = ft_strslen(strs);
	if (strslen != 3)
		serialize_error(ERROR_SYNTAX_AMBIENCE, 255, data, strs);
	if (!ft_isfloatable(strs[1]))
		serialize_error(ERROR_SYNTAX_AMBIENCE, 255, data, strs);
	data->ambience->intensity = ft_atof(strs[1]);
	if (ft_flt(data->ambience->intensity, 0)
		|| ft_fgt(data->ambience->intensity, 1))
		serialize_error(ERROR_INVALID_AMBIENCE, 255, data, strs);
	strsrgb = ft_split_any(strs[2], ',');
	if (!strsrgb)
		serialize_error(ERROR_ERRNO, errno, data, strs);
	set_color(data, strs, strsrgb);
	ft_strsfree(strsrgb);
}

t_data	*serialize_a(t_data *data, char **strs)
{
	t_ambience	*ambience;

	if (data->ambience)
		serialize_error(ERROR_DUPLICATE_AMBIENCE, 255, data, strs);
	if (!alloca_to((void **)&ambience, sizeof(t_ambience)))
		serialize_error(ERROR_ERRNO, errno, data, strs);
	data->ambience = ambience;
	set_ambience(data, strs);
	return (data);
}
