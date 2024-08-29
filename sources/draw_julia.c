/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:59:17 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/29 17:06:54 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	draw_julia(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_julia(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_connect, data->window, data->img, 0, 0);
}

void	draw_julia2(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_julia2(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_connect, data->window, data->img, 0, 0);
}

void	draw_julia3(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_julia3(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_connect, data->window, data->img, 0, 0);
}

void	draw_julia4(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_julia4(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_connect, data->window, data->img, 0, 0);
}
