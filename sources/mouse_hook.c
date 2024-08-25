/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:22 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/25 21:58:55 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Increases the visible area of the fractal, making it appear smaller
void	zoom_out(t_data *data, double zoom_factor,
		double center_re, double center_im)
{
	data->min_re = center_re - (center_re - data->min_re) * zoom_factor;
	data->max_re = center_re + (data->max_re - center_re) * zoom_factor;
	data->min_im = center_im - (center_im - data->min_im) * zoom_factor;
	data->max_im = center_im + (data->max_im - center_im) * zoom_factor;
}

// Decreases the visible area of the fractal, making it appear larger
void	zoom_in(t_data *data, double zoom_factor,
		double center_re, double center_im)
{
	data->min_re = center_re - (center_re - data->min_re) / zoom_factor;
	data->max_re = center_re + (data->max_re - center_re) / zoom_factor;
	data->min_im = center_im - (center_im - data->min_im) / zoom_factor;
	data->max_im = center_im + (data->max_im - center_im) / zoom_factor;
}

// Handles mouse events for zooming in and out of the fractal
int	mouse_event(int button, int x, int y, t_data *data)
{
	double	zoom_factor;
	double	center_re;
	double	center_im;

	(void)x;
	(void)y;
	zoom_factor = 2.0;
	center_re = (data->min_re + data->max_re) / 2.0;
	center_im = (data->min_im + data->max_im) / 2.0;
	if (button == 4)
		zoom_in(data, zoom_factor, center_re, center_im);
	else if (button == 5)
		zoom_out(data, zoom_factor, center_re, center_im);
	draw_fractal(data);
	return (0);
}
