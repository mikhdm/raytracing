NAME = miniRT
CC = clang
CFLAGS = -Wall -Wextra -Werror -MMD -Ofast -I ./include -I ./lib/libft -I ./lib/libft/get_next_line -I ./lib/mlx

LIBFT_DIR = ./lib/libft
MLX_DIR = ./lib/mlx

SRCS =  src/rt/utils/calc_quad_equation.c \
        src/rt/utils/calc_ray_point.c \
        src/rt/utils/calc_sphere_orient.c \
        src/rt/utils/deg_to_rad.c \
        src/rt/utils/rad_to_deg.c \
        src/rt/utils/swap_double.c \
        src/rt/utils/gen_square_vertices.c \
        src/rt/utils/alloca_to.c \
        src/rt/utils/is_polygon_point.c \
        src/rt/utils/calc_min_t.c \
        src/rt/utils/calc_cylinder_min_t.c \
        src/rt/utils/calc_triangle_orient.c \
        src/rt/utils/calc_cylinder_orient.c \
        src/rt/utils/calc_faceted_orient.c \
        src/rt/utils/isdir.c \
        src/rt/utils/skip_spaces_str.c \
		src/rt/utils/mlx_reset_image.c \
		src/rt/utils/get_cam.c \
		src/rt/utils/look_at.c \
		src/rt/utils/intersect_planar.c \
		src/rt/utils/one_of.c \
        src/parsing/parse.c \
        src/parsing/errors.c \
        src/parsing/cleanup.c \
        src/parsing/serialize.c \
        src/parsing/serializers/serialize_r.c \
        src/parsing/serializers/serialize_a.c \
		src/parsing/serializers/serialize_c.c \
		src/parsing/serializers/serialize_l.c \
		src/parsing/serializers/serialize_sp.c \
		src/parsing/serializers/serialize_cy.c \
		src/parsing/serializers/serialize_pl.c \
		src/parsing/serializers/serialize_tr.c \
		src/parsing/serializers/serialize_sq.c \
		src/parsing/serializers/helpers/serialize_point.c \
		src/parsing/serializers/helpers/serialize_orient.c \
		src/parsing/serializers/helpers/serialize_rgb.c \
		src/parsing/serializers/helpers/lst_figure_append.c \
		src/parsing/serializers/helpers/serialize_cy_rgb.c \
		src/parsing/serializers/helpers/serialize_sq_rgb.c \
		src/parsing/serializers/helpers/serialize_pl_rgb.c \
        src/parsing/validators/valid_rgb.c \
        src/parsing/validators/valid_orient.c \
        src/parsing/validators/valid_point3.c \
        src/rt/canvas.c \
        src/rt/color.c \
        src/rt/colorex.c \
        src/rt/event.c \
        src/rt/intersect.c \
        src/rt/light.c \
        src/rt/linop.c \
        src/rt/linopex.c \
        src/rt/rayop.c \
        src/rt/render.c \
        src/rt/shade.c \
        src/screenshot.c \
        main.c
		
INCLUDES = 	./lib/mlx/mlx.h \
			./lib/libft/libft.h \
			./lib/libft/get_next_line.h \
			./include/utils.h \
		   	./include/canvas.h \
		   	./include/color.h \
			./include/event.h \
		   	./include/intersect.h \
			./include/linop.h \
			./include/rayop.h \
			./include/render.h \
			./include/screenshot.h \
			./include/shade.h \
			./include/light.h \
			./include/parsing/errors.h \
			./include/parsing/parse.h \
			./include/parsing/serialize.h
		   
OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

all: libft $(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -framework OpenGL -framework AppKit -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx $(OBJS) -o $(NAME)

libft:
	$(MAKE) -C $(LIBFT_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	rm -f $(DEPS) 

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re