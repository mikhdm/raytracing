#include "color.h"
#include <math.h>

int	addargb(int argb_left, int argb_right)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = (a_component(argb_left) + a_component(argb_right)) / 2;
	r = (r_component(argb_left) + r_component(argb_right)) / 2;
	g = (g_component(argb_left) + g_component(argb_right)) / 2;
	b = (b_component(argb_left) + b_component(argb_right)) / 2;
	return (argb_color(a, r, g, b));
}

int	multargb(int argb_left, int argb_right)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = (a_component(argb_left) * a_component(argb_right)) / 255;
	r = (r_component(argb_left) * r_component(argb_right)) / 255;
	g = (g_component(argb_left) * g_component(argb_right)) / 255;
	b = (b_component(argb_left) * b_component(argb_right)) / 255;
	return (argb_color(a, r, g, b));
}

int	cmultargb(int argb, double const value)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = (int)(a_component(argb) * value);
	r = (int)(r_component(argb) * value);
	g = (int)(g_component(argb) * value);
	b = (int)(b_component(argb) * value);
	return (argb_color(a, r, g, b));
}

int	linargb(int argb)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = (int)(pow(a_component(argb) / 255.0, GAMMA_COEF) * 255);
	r = (int)(pow(r_component(argb) / 255.0, GAMMA_COEF) * 255);
	g = (int)(pow(g_component(argb) / 255.0, GAMMA_COEF) * 255);
	b = (int)(pow(b_component(argb) / 255.0, GAMMA_COEF) * 255);
	return (argb_color(a, r, g, b));
}

int	gammargb(int argb)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = (int)(pow(a_component(argb) / 255.0, GAMMA_REVERSE_COEF) * 255);
	r = (int)(pow(r_component(argb) / 255.0, GAMMA_REVERSE_COEF) * 255);
	g = (int)(pow(g_component(argb) / 255.0, GAMMA_REVERSE_COEF) * 255);
	b = (int)(pow(b_component(argb) / 255.0, GAMMA_REVERSE_COEF) * 255);
	return (argb_color(a, r, g, b));
}
