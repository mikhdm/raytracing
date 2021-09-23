#include "canvas.h"
#include "libft.h"
#include "parsing/serialize.h"
#include "parsing/errors.h"
#include <stddef.h>

void	serialize_pl_rgb(t_data *data, char **strs, char **strs_rgb,
						 t_plane **plane)
{
	int		argb;

	argb = COLOR_BACKGROUND;
	if (!serialize_rgb(strs_rgb, &argb))
	{
		ft_strsfree(strs_rgb);
		serialize_error(ERROR_INVALID_PLANE, 255, data, strs);
	}
	(*plane)->color = argb;
	ft_strsfree(strs_rgb);
	strs_rgb = NULL;
}
