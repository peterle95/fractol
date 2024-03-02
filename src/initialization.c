/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:42:34 by pmolzer           #+#    #+#             */
/*   Updated: 2024/02/21 01:42:34 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* clean_init:
*	Initializes the fractol data structure with default
*	values to be replaced later. Used for error detection.
*/
void	clean_init(t_fractol *fractal_data)
{
	// why they all have different values?
	fractal_data->mlx = NULL;
	fractal_data->win = NULL;
	fractal_data->img = NULL;
	fractal_data->buf = NULL;
	fractal_data->set = -1;
	fractal_data->min_r = 0;
	fractal_data->max_r = 0;
	fractal_data->min_i = 0;
	fractal_data->max_i = 0;
	fractal_data->kr = 0;
	fractal_data->ki = 0;
	fractal_data->sx = 0;
	fractal_data->rx = 0;
	fractal_data->fx = 0;
	fractal_data->palette = NULL;
	fractal_data->color_pattern = -1;
	fractal_data->color = 0;
}

/* get_complex_layout:
*	Maps the complex number axes to the window width and height to
*	create an equivalence between a given pixel and a complex number.
*		- The Mandelbox set real and imaginary axes range from 4 to -4
*		so the edges are mapped to those numbers for the fractal to appear
*		centered.
*		- Julia needs a bit more space to the right than Mandelbrot or
*		Burning Ship, so the mapping must also be shifted slightly.
*	Also, one of the edges is always calculated according to the other edges
*	to avoid fractal distortion if the window proportions change.
*/
void	get_complex_layout(t_fractol *fractal_data)
{
	if (fractal_data->set == MANDELBOX)
	{
		fractal_data->min_r = -4.0;
		fractal_data->max_r = 4.0;
		fractal_data->min_i = -4.0;
		fractal_data->max_i = fractal_data->min_i + (fractal_data->max_r - fractal_data->min_r) * HEIGHT / WIDTH;
	}
	else if (fractal_data->set == JULIA)
	{
		fractal_data->min_r = -2.0;
		fractal_data->max_r = 2.0;
		fractal_data->min_i = -2.0;
		fractal_data->max_i = fractal_data->min_i + (fractal_data->max_r - fractal_data->min_r) * HEIGHT / WIDTH;
	}
	else // do I need the else statement?
	{
		fractal_data->min_r = -2.0;
		fractal_data->max_r = 1.0;
		fractal_data->max_i = -1.5;
		fractal_data->min_i = fractal_data->max_i + (fractal_data->max_r - fractal_data->min_r) * HEIGHT / WIDTH;
	}
}

/* init_img:
*	Initializes an MLX image and a color palette. The color palette will
*	be used to store every shade of color for every iteration number,
*	and the color of each pixel will be stored in the image, which will
*	then be displayed in the program window.
*/
static void	init_img(t_fractol *fractal_data)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buf;

	fractal_data->palette = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	if (!(fractal_data->palette))
		clean_exit(msg("error initializing color scheme.", "", 1), f);
	fractal_data->img = mlx_new_image(fractal_data->mlx, WIDTH, HEIGHT);
	if (!(fractal_data->img))
		clean_exit(msg("image creation error.", "", 1), f);
	buf = mlx_get_data_addr(fractal_data->img, &pixel_bits, &line_bytes, &endian);
	fractal_data->buf = buf;
}

/* reinit_image:
*	Cleanly reinitializes the MLX image if the color palette or 
*	fractal type is modified at runtime.
*/
void	reinit_img(t_fractol *fractal_data)
{
	if (fractal_data->mlx && fractal_data->img)
		mlx_destroy_image(fractal_data->mlx, fractal_data->img);
	if (fractal_data->palette)
		free(fractal_data->palette);
	if (fractal_data->buf)
		fractal_data->buf = NULL;
	init_img(f);
}

/* init:
*	Creates a new MLX instance, a new window and populates
*	the fractol data structure with default values.
*/
void	init(t_fractol *fractal_data)
{
	fractal_data->mlx = mlx_init();
	if (!fractal_data->mlx)
		clean_exit(msg("MLX: error connecting to mlx.", "", 1), f);
	fractal_data->win = mlx_new_window(fractal_data->mlx, WIDTH, HEIGHT, "Fractol");
	if (!fractal_data->win)
		clean_exit(msg("MLX: error creating window.", "", 1), f);
	fractal_data->sx = 2.0;
	fractal_data->rx = 0.5;
	fractal_data->fx = 1.0;
	get_complex_layout(f);
}
