/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:34:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/29 17:04:36 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Calculates and draws a pixel for the Mandelbrot set
void	pixel_mandelbrot(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot(cr, ci);
	my_mlx_pixel_put(data, x, y, color);
}

// Calculates and draws a pixel for a variation of the Mandelbrot set
void	pixel_mandelbrot2(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot2(cr, ci);
	my_mlx_pixel_put(data, x, y, color);
}

// Calculates and draws a pixel for another variation of the Mandelbrot set
void	pixel_mandelbrot3(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot3(cr, ci);
	my_mlx_pixel_put(data, x, y, color);
}

// Calculates and draws a pixel for a fourth variation of the Mandelbrot set
void	pixel_mandelbrot4(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot4(cr, ci);
	my_mlx_pixel_put(data, x, y, color);
}
