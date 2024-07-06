/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:54:25 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/06 20:55:29 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int color_mandelbrot(double cr, double ci)
{
    int iterations;
    iterations = mandelbrot(cr , ci);
    return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}


void pixel_mandelbrot(t_data *data, int x, int y)
{
    double cr;
    double ci;
    int color;

    cr = calculate_cr(data, x);
    ci = calculate_ci(data, y);
    color = color_mandelbrot(cr, ci);
    mlx_pixel_put(data->mlx, data->win, x, y, color);
}

static int color_mandelbrot2(double cr, double ci)
{
    int iterations;
    iterations = mandelbrot(cr , ci);
    return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}


void pixel_mandelbrot2(t_data *data, int x, int y)
{
    double cr;
    double ci;
    int color;

    cr = calculate_cr(data, x);
    ci = calculate_ci(data, y);
    color = color_mandelbrot2(cr, ci);
    mlx_pixel_put(data->mlx, data->win, x, y, color);
}

static int color_mandelbrot3(double cr, double ci)
{
    int iterations;
    iterations = mandelbrot(cr , ci);
    return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}


void pixel_mandelbrot3(t_data *data, int x, int y)
{
    double cr;
    double ci;
    int color;

    cr = calculate_cr(data, x);
    ci = calculate_ci(data, y);
    color = color_mandelbrot3(cr, ci);
    mlx_pixel_put(data->mlx, data->win, x, y, color);
}

static int color_mandelbrot4(double cr, double ci)
{
    int iterations;
    iterations = mandelbrot(cr , ci);
    return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}


void pixel_mandelbrot4(t_data *data, int x, int y)
{
    double cr;
    double ci;
    int color;

    cr = calculate_cr(data, x);
    ci = calculate_ci(data, y);
    color = color_mandelbrot4(cr, ci);
    mlx_pixel_put(data->mlx, data->win, x, y, color);
}