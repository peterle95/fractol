/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:59:24 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/22 16:27:02 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*This function is responsible for drawing the entire Mandelbrot set:

It uses two nested loops to iterate over EVERY PIXEL in the window.
The outer loop (y) goes from top to bottom of the window.
The inner loop (x) goes from left to right for each row.
For each pixel, it calls pixel_mandelbrot to calculate and draw the color for that pixel.*/
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
}

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
}

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
}

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
}
