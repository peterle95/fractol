/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:27 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/06 21:13:38 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*Julia Set Concept:

The Julia set is closely related to the Mandelbrot set, but with a key difference.
While the Mandelbrot set uses the same starting point (0, 0) for each pixel and varies the constant c, the Julia set uses a fixed c and varies the starting point z.


The julia function:

This function takes five parameters: zr and zi (the real and imaginary parts of the starting point), cr and ci (the real and imaginary parts of the constant c), and max_iterations.
It applies the same iterative formula as the Mandelbrot set: z = z^2 + c
The iteration continues until either |z| > 2 or we reach max_iterations.
The number of iterations determines the color of the point.


The draw_julia function:

Similar to draw_mandelbrot, this function iterates over each pixel of the window.
For each pixel, it maps the pixel coordinates to a point in the complex plane (zr, zi).
It calls the julia function for each point, using the fixed values of cr and ci (stored in data->julia_cr and data->julia_ci).
Based on the number of iterations, it assigns a color to the pixel.


Differences from Mandelbrot:

In the Mandelbrot set, we start with z = 0 and use the pixel coordinates for c.
In the Julia set, we use the pixel coordinates for z and use a fixed value for c.
This fixed c value determines the specific Julia set we're drawing.


Julia Set Variety:

Different values of c result in different Julia sets.
This is why we store julia_cr and julia_ci in the data structure - they can be set based on user input or program parameters.


Performance and Optimization:

Like the Mandelbrot set, this basic implementation can be slow for high resolutions or iteration counts.
The same optimization techniques (lookup tables, multi-threading, GPU acceleration) can be applied.*/
/* int julia(double zr, double zi, double cr, double ci, int max_iterations)
{
    int n = 0;
    double zr_new;

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

int julia(double zr, double zi, double cr, double ci)
{
    double zr2 = zr * zr;
    double zi2 = zi * zi;
    int n = 0;

    while (zr2 + zi2 <= 4.0 && n < MAX_ITERATIONS)
    {
        zi = 2 * zr * zi + ci;
        zr = zr2 - zi2 + cr;
        zr2 = zr * zr;
        zi2 = zi * zi;
        n++;
    }
    return (n);
}

double calculate_zr(t_data *data, int x)
{
    return (data->min_re + (double)x * (data->max_re - data->min_re) / WIN_WIDTH);
}

double calculate_zi(t_data *data, int y)
{
    return (data->min_im + (double)y * (data->max_im - data->min_im) / WIN_HEIGHT);
}

void draw_julia(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_julia(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_julia2(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_julia2(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_julia3(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_julia3(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_julia4(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_julia4(data, x, y);
            x++;
        }
        y++;
    }
}