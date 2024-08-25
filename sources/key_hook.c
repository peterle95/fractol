/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:22:02 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/25 22:22:04 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Handles key press events for movement and exit
void	key_pressed(t_data *data, int keycode, double *move_x, double *move_y)
{
	if (keycode == 65307)
		exit_program(data);
	else if (keycode == 65361)
		*move_x = -0.1;
	else if (keycode == 65363)
		*move_x = 0.1;
	else if (keycode == 65362)
		*move_y = -0.1;
	else if (keycode == 65364)
		*move_y = 0.1;
}

// Applies movement to the fractal viewing window
void	apply_movement(t_data *data, double move_x, double move_y)
{
	double	range_re;
	double	range_im;

	range_re = data->max_re - data->min_re;
	range_im = data->max_im - data->min_im;
	data->min_re = data->min_re + (move_x * range_re);
	data->max_re = data->max_re + (move_x * range_re);
	data->min_im = data->min_im + (move_y * range_im);
	data->max_im = data->max_im + (move_y * range_im);
	draw_fractal(data);
}

// Main key hook function to handle all keyboard inputs
int	key_hook(int keycode, t_data *data)
{
	double	move_x;
	double	move_y;
	int		fractal_changed;

	move_x = 0;
	move_y = 0;
	fractal_changed = 0;
	if (keycode == 65307 || (keycode >= 65361 && keycode <= 65364))
		key_pressed(data, keycode, &move_x, &move_y);
	else if (keycode >= 49 && keycode <= 56)
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
