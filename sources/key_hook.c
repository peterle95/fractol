
#include "../includes/fractol.h"

int	key_pressed(t_data *data, int keycode, double move_x, double move_y)
{
	if (keycode == 65307) // ESC key
		exit_program(data);
	else if (keycode == 65361) // Key Left
		move_x = -0.1;
	else if (keycode == 65363) // Key Right
		move_x = 0.1;
	else if (keycode == 65362) // Key UP
		move_y = -0.1;
	else if (keycode == 65364) // Key Down
		move_y = 0.1;
	return (move_x, move_y);
}

void	apply_movement(t_data *data, double move_x, double move_y)
{
	double	range_re;
	double	range_im;

	range_re = data->max_re - data->min_re;
	range_im = data->max_im - data->min_im;
	data->min_re += move_x * range_re;
	data->max_re += move_x * range_re;
	data->min_im += move_y * range_im;
	data->max_im += move_y * range_im;
	draw_fractal(data);
}

// think about assigning 0.1 to MOVE_STEP. And the keys as well
int	key_hook(int keycode, t_data *data)
{
	double	move_x;
	double	move_y;
	int		fractal_changed;

	move_x = 0;
	move_y = 0;
	fractal_changed = 0;
	if (keycode == 65307 || (keycode >= 65361 && keycode <= 65364))
		key_pressed(data, keycode, move_x, move_y);
	else if (keycode >= 49 && keycode <= 56) // Keys between 1-8
	{
		data->fractal_type = keycode - 49;
		fractal_changed = 1;
	}
	else
		return (0);
	if (move_x != 0 || move_y != 0)
		apply_movement(data, move_x, move_y);
	if (fractal_changed != 0)
		draw_fractal(data);
	return (0);
}
