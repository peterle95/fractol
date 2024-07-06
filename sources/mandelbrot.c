/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:32 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/06 20:53:19 by pmolzer          ###   ########.fr       */
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

int mandelbrot(double cr, double ci)
{
    double zr;
    double zi;
    double temp;
    int n;

    zr = 0.0;
    zi = 0.0;
    n = 0;
    while (zr * zr + zi * zi <= 4.0 && n < MAX_ITERATIONS)
    {
        temp = 2 * zr * zi + ci;
        zr = zr * zr - zi * zi + cr;
        zi = temp;
        n++;
    }
    return (n);
}

double calculate_cr(t_data *data, int x)
{
    return (data->min_re + (double)x * (data->max_re - data->min_re) / WIN_WIDTH);
}

double calculate_ci(t_data *data, int y)
{
    return (data->min_im + (double)y * (data->max_im - data->min_im) / WIN_HEIGHT);
}

void draw_mandelbrot(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_mandelbrot(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_mandelbrot2(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_mandelbrot2(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_mandelbrot3(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_mandelbrot3(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_mandelbrot4(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_mandelbrot4(data, x, y);
            x++;
        }
        y++;
    }
}
