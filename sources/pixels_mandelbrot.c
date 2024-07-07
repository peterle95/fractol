/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:34:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/07 20:34:32 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	pixel_mandelbrot(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot(cr, ci);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_mandelbrot2(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot2(cr, ci);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_mandelbrot3(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot3(cr, ci);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_mandelbrot4(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot4(cr, ci);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}