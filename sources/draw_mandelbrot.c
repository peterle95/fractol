/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:59:24 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/29 17:07:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Draws the standard Mandelbrot set
void	draw_mandelbrot(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_mandelbrot(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_connect, data->window, data->img, 0, 0);
}

// Draws a variation of the Mandelbrot set (Mandelbrot2)
void	draw_mandelbrot2(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_mandelbrot2(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_connect, data->window, data->img, 0, 0);
}

// Draws another variation of the Mandelbrot set (Mandelbrot3)
void	draw_mandelbrot3(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_mandelbrot3(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_connect, data->window, data->img, 0, 0);
}

// Draws a fourth variation of the Mandelbrot set (Mandelbrot4)
void	draw_mandelbrot4(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_mandelbrot4(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_connect, data->window, data->img, 0, 0);
}
