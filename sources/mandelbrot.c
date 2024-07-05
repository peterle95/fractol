/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:32 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/05 11:56:03 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*The mandelbrot function:

This function implements the core Mandelbrot set algorithm.
It takes a complex number (cr + ci*i) as input, which represents a point in the complex plane.
It iterates the function f(z) = z^2 + c, where c is the input complex number.
The iteration continues until either the absolute value of z exceeds 2 (which means the point is not in the Mandelbrot set) or we reach the maximum number of iterations.
The number of iterations it takes to exceed 2 determines the color of the point.


The draw_mandelbrot function:

This function iterates over each pixel of the window.
For each pixel, it maps the pixel coordinates to a point in the complex plane.
It calls the mandelbrot function for each point to determine the number of iterations.
Based on the number of iterations, it assigns a color to the pixel.
Finally, it puts the pixel on the image using a my_mlx_pixel_put function (which you'll need to implement).


Mapping pixels to complex plane:

The mapping from pixel coordinates to complex plane coordinates is done using linear interpolation.
This allows us to zoom and pan around the fractal by adjusting min_re, max_re, min_im, and max_im.


Coloring:

The coloring scheme here is very basic, just mapping the number of iterations linearly to a grayscale value.
You can create more interesting color schemes by using more sophisticated mapping functions.


Performance considerations:

This basic implementation can be slow for high resolutions or high iteration counts.
Optimizations could include using a lookup table for the squared terms, multi-threading, or even GPU acceleration.*/

/* int mandelbrot(double cr, double ci, int max_iterations)
{
    double zr = 0.0;
    double zi = 0.0;
    double zr_new;
    int n = 0;

    while (n < max_iterations)
    {
        if (zr * zr + zi * zi > 4.0)
            return n;
        zr_new = zr * zr - zi * zi + cr;
        zi = 2 * zr * zi + ci;
        zr = zr_new;
        n++;
    }
    return max_iterations;
} */

// rimuovi max_iterations e usa lo struct
int	mandelbrot(double cr, double ci, int max_iterations)
{
	double	zr;
	double	zi;
	double	zr2;
	double	zi2;
	int		n;

	n = 0;
	zr = 0.0;
	zi = 0.0;
	while (zr2 + zi2 <= 4.0 && n < max_iterations)
	{
		zi = 2 * zr * zi + ci;
		zr = zr2 - zi2 + cr;
		zr2 = zr * zr;
		zi2 = zi * zi;
		n++;
	}
	return (n);
}

// too many varibles declarations in a function --> do the same as in julia
void	draw_mandelbrot(t_data *data)
{
	int		x;
	int		y;
	double	cr;
	double	ci;
	int		iterations;
	int		color;

	y = 0;
	x = 0;
	while (y < WIN_HEIGHT)
	{
		while (x < WIN_WIDTH)
		{
			cr = data->min_re + (double)x * (data->max_re - data->min_re) / WIN_WIDTH;
			ci = data->min_im + (double)y * (data->max_im - data->min_im) / WIN_HEIGHT;
			iterations = mandelbrot(cr, ci, MAX_ITERATIONS);
			color = iterations * 0xFFFFFF / MAX_ITERATIONS;
			mlx_pixel_put(data->mlx, data->win, x, y, color);
			x++;
		}
	y++;
	}
}

/*
void draw_mandelbrot2(t_data *data)
{
    int x, y;
    double cr, ci;

    for (y = 0; y < WIN_HEIGHT; y++)
    {
        for (x = 0; x < WIN_WIDTH; x++)
        {
            cr = data->min_re + (double)x * (data->max_re - data->min_re) / WIN_WIDTH;
            ci = data->min_im + (double)y * (data->max_im - data->min_im) / WIN_HEIGHT;
            int iterations = mandelbrot(cr, ci, MAX_ITERATIONS);
            int color = iterations * 0x561662 / MAX_ITERATIONS;
            mlx_pixel_put(data->mlx, data->win, x, y, color);
        }
    }
}

void draw_mandelbrot3(t_data *data)
{
    int x, y;
    double cr, ci;

    for (y = 0; y < WIN_HEIGHT; y++)
    {
        for (x = 0; x < WIN_WIDTH; x++)
        {
            cr = data->min_re + (double)x * (data->max_re - data->min_re) / WIN_WIDTH;
            ci = data->min_im + (double)y * (data->max_im - data->min_im) / WIN_HEIGHT;
            int iterations = mandelbrot(cr, ci, MAX_ITERATIONS);
            int color = iterations * 0xc7e400 / MAX_ITERATIONS;
            mlx_pixel_put(data->mlx, data->win, x, y, color);
        }
    }
}

void draw_mandelbrot4(t_data *data)
{
    int x, y;
    double cr, ci;

    for (y = 0; y < WIN_HEIGHT; y++)
    {
        for (x = 0; x < WIN_WIDTH; x++)
        {
            cr = data->min_re + (double)x * (data->max_re - data->min_re) / WIN_WIDTH;
            ci = data->min_im + (double)y * (data->max_im - data->min_im) / WIN_HEIGHT;
            int iterations = mandelbrot(cr, ci, MAX_ITERATIONS);
            int color = iterations * 0x0000EE / MAX_ITERATIONS;
            mlx_pixel_put(data->mlx, data->win, x, y, color);
        }
    }
}*/
