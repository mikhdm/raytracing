#include "canvas.h"
#include "event.h"
#include "render.h"
#include "screenshot.h"
#include "parsing/errors.h"
#include "parsing/parse.h"
#include "parsing/cleanup.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

static	short	check(int argc, char **argv)
{
	char	*p;

	p = NULL;
	if (argc == 1)
		ft_pexit(ERROR_PATH_PARAM_EMPTY, 255);
	if (argc == 2 || argc == 3)
	{
		p = ft_strrchr(argv[1], '.');
		if (!p || (ft_strcmp(p, ".rt") != 0))
			ft_pexit(ERROR_SCENE_EXT_WRONG, 255);
		if (argc == 3)
		{
			if (ft_strcmp(argv[2], ARGV_SCREENSHOT) != 0)
				ft_pexit(ERROR_SCREENSHOT_PARAM_WRONG, 255);
			else
				return (DO_SCREENSHOT);
		}
		return (DO_WINDOW);
	}
	ft_perror(ERROR_NUM_ARGS_WRONG);
	exit(255);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_pair_double	range;
	short			status;

	data = NULL;
	status = check(argc, argv);
	range = (t_pair_double){.first = 1.0, .second = INFINITY};
	if (status == DO_SCREENSHOT)
	{
		data = parse(argv[1]);
		init(data, FALSE);
		render(data, data->cam, &range);
		screenshot(data, "screenshot.bmp");
		cleanup(data);
	}
	else
	{
		data = parse(argv[1]);
		init(data, TRUE);
		render(data, data->cam, &range);
		mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
		bind_hooks(data);
		mlx_loop(data->mlx);
	}
	return (0);
}
