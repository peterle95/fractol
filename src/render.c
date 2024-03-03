/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:43:19 by pmolzer           #+#    #+#             */
/*   Updated: 2024/02/21 01:43:19 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* set_pixel_color:
	Add a color to one pixel of the MLX image map.
	The MLX image is composed of 32 bits per pixel.
	Color ints are stored from right to left, here, and are in
	the form of 0xAARRGGBB. 8 bits encode each color component,
	Alpha (Transparency), Red, Green and Blue.
	Bit shifting:
		- BB >> 0   (0x000000BB)
		- GG >> 8   (0x0000GG00)
		- RR >> 16  (0x00RR0000)
		- AA >> 24  (0xAA000000)
*/
void	set_pixel_color(t_fractol *f, int x, int y, int color)
{
	fractal_data->buf[x * 4 + y * WIDTH * 4] = color;
	fractal_data->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
	fractal_data->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
	fractal_data->buf[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}

/* calculate_fractal:
*	Picks the correct fractal calculation function depending
*	on the current fractal set.
*/
int	calculate_fractal(t_fractol *f, double pr, double pi)
{
	int	nb_iter;

	if (fractal_data->set == MANDELBROT)
		nb_iter = mandelbrot(pr, pi);
	else if (fractal_data->set == JULIA)
		nb_iter = julia(f, pr, pi);
	return (nb_iter);
}

/* render:
*	Iterates through each pixel of the window, translates the pixel's
*	coordinates into a complex number to be able to calculate if that number
*	is part of the fractal set or not.
*	The number of iterations that complex number goes through before being
*	rejected from the fractal set determines which color is applied to the pixel.
*	Once all pixels have been assessed and added to the MLX image,
*	this function displays the MLX image to the window.
*/
void	render(t_fractol *fractal_data)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	int		nb_iter;

	mlx_clear_window(fractal_data->mlx, fractal_data->win);
	y = -1; // why do we need this, and it's set as a -1, should it be constant?
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = fractal_data->min_r + (double)x * (fractal_data->max_r - fractal_data->min_r) / WIDTH;
			pi = fractal_data->max_i + (double)y * (fractal_data->min_i - fractal_data->max_i) / HEIGHT;
			nb_iter = calculate_fractal(f, pr, pi);
			set_pixel_color(f, x, y, fractal_data->palette[nb_iter]);
		}
	}
	mlx_put_image_to_window(fractal_data->mlx, fractal_data->win, fractal_data->img, 0, 0);
}
