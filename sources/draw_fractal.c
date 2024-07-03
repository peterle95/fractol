/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:34 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/03 22:10:21 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void draw_fractal(t_data *data)
{
    if (data->fractal_type == MANDELBROT)
        draw_mandelbrot(data);
    else if (data->fractal_type == MANDELBROT2)
        draw_mandelbrot2(data);
    else if (data->fractal_type == MANDELBROT3)
        draw_mandelbrot3(data);
    else if (data->fractal_type == MANDELBROT4)
        draw_mandelbrot4(data);
    else if (data->fractal_type == JULIA)
        draw_julia(data);
    else if (data->fractal_type == JULIA2)
        draw_julia2(data);
    else if (data->fractal_type == JULIA3)
        draw_julia3(data);
    else if (data->fractal_type == JULIA4)
        draw_julia4(data);
    // Add more fractal types here if needed
}