/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_julia.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:34:35 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/07 20:34:37 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	pixel_julia(t_data *data, int x, int y)
{
	double	zr;
	double	zi;
	int		color;

	zr = calculate_zr(data, x);
	zi = calculate_zi(data, y);
	color = color_julia(data, zr, zi);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_julia2(t_data *data, int x, int y)
{
	double	zr;
	double	zi;
	int		color;

	zr = calculate_zr(data, x);
	zi = calculate_zi(data, y);
	color = color_julia2(data, zr, zi);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_julia3(t_data *data, int x, int y)
{
	double	zr;
	double	zi;
	int		color;

	zr = calculate_zr(data, x);
	zi = calculate_zi(data, y);
	color = color_julia3(data, zr, zi);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_julia4(t_data *data, int x, int y)
{
	double	zr;
	double	zi;
	int		color;

	zr = calculate_zr(data, x);
	zi = calculate_zi(data, y);
	color = color_julia4(data, zr, zi);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}
