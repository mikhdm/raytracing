#ifndef COLOR_H
# define COLOR_H

# define GAMMA_COEF 2.2
# define GAMMA_REVERSE_COEF 0.4545

int		a_component(int argb);
int		r_component(int argb);
int		g_component(int argb);
int		b_component(int argb);
int		argb_color(int a, int r, int g, int b);
int		linargb(int argb);
int		gammargb(int argb);
int		addargb(int argb_left, int argb_right);
int		multargb(int argb_left, int argb_right);
int		cmultargb(int argb, double value);

#endif
