#ifndef CANVAS_H
# define CANVAS_H

# include "linop.h"
# include "libft.h"

# define COLOR_BACKGROUND 0x2dc3fa
# define COLOR_BLACK 0x0

# define LABEL_SPHERE		"sp"
# define LABEL_PLANE		"pl"
# define LABEL_SQUARE		"sq"
# define LABEL_CYLINDER		"cy"
# define LABEL_TRIANGLE		"tr"
# define LABEL_LIGHT		"l"
# define LABEL_CAMERA		"c"
# define LABEL_AMBIENCE		"A"
# define LABEL_RESOLUTION	"R"

# define NUM_LABELS			9

# define DO_SCREENSHOT      1
# define DO_WINDOW          2

# define WINDOW_TITLE		"miniRT"

typedef struct s_screen
{
	int			width;
	int			height;
	char		*title;
}				t_screen;

typedef struct s_viewport
{
	double		width;
	double		height;
}				t_viewport;

typedef struct s_ambience
{
	double		intensity;
	int			color;
}				t_ambience;

typedef struct s_light
{
	double			brightness;
	int				color;
	t_vector3		center;
	struct s_light	*next;
}					t_light;

typedef struct s_camera
{
	double			fov;
	short			active;
	t_vector3		center;
	t_vector3		orient;
	t_viewport		*viewport;
	struct s_camera	*next;
}					t_camera;

typedef struct s_sphere
{
	int				color;
	double			diameter;
	t_vector3		center;
}					t_sphere;

typedef struct s_plane
{
	int				color;
	t_vector3		center;
	t_vector3		orient;
}					t_plane;

typedef struct s_square
{
	int				color;
	double			size;
	t_vector3		center;
	t_vector3		orient;
}					t_square;

typedef struct s_cylinder
{
	int					color;
	double				diameter;
	double				height;
	t_vector3			center;
	t_vector3			orient;
}						t_cylinder;

typedef struct s_triangle
{
	t_vector3			x;
	t_vector3			y;
	t_vector3			z;
	int					color;
}						t_triangle;

typedef struct s_figure
{
	char			*label;
	void			*content;
	struct s_figure	*next;

}					t_figure;

/*
*
* t_data - structure to store all parsed data & window meta information.
*
*/
typedef struct s_data
{
	int			bpp;
	int			length;
	int			endian;
	char		*addr;
	void		*mlx;
	void		*window;
	void		*img;
	int			fildes;
	t_screen	*screen;
	t_camera	*cam;
	t_light		*light;
	t_ambience	*ambience;
	t_figure	*figures;
}				t_data;

/*
*
* putpixel - function which put color defined by color param
* into canvas pointed by x and y. Converting from canvas to screen is done
* automatically.
*
*/
void		putpixel(t_data *data, int x, int y, int color);

/*
*
*	calc_viewport - calculates width & height of a viewport.
*
*/
t_viewport	calc_viewport(t_data *data, t_camera *cam);
t_vector3	canvas_to_viewport(t_data *data, t_camera *cam, int x, int y);
void		init(t_data *data, short windowed);

#endif
