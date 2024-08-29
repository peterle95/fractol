/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:24 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/29 17:01:59 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Initializes the fractal parameters and viewing window
void	init_fractal(t_data *data)
{
	data->min_re = -2.0;
	data->max_re = 1.0;
	data->min_im = -1.5;
	data->max_im = data->min_im
		+ (data->max_re - data->min_re) * WINDOW_HEIGHT / WINDOW_WIDTH;
	data->julia_ci = 0.15;
	data->julia_cr = -0.8;
}

int	create_image(t_data *data)
{
	data->img = mlx_new_image(data->mlx_connect, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		return (0);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	return (1);
}

// Initializes the MLX connection, creates a window, 
// and sets up initial fractal data
int	init_data(t_data *data)
{
	data->mlx_connect = mlx_init();
	if (!data->mlx_connect)
		return (0);
	data->window = mlx_new_window(data->mlx_connect,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Fract'ol");
	if (!data->window)
		return (0);
	if (!create_image(data))
		return (0);
	init_fractal(data);
	return (1);
}
