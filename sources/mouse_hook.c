/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:22 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/12 23:11:16 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	zoom_out(t_data *data, double zoom_factor,
		double center_re, double center_im)
{
	data->zoom /= zoom_factor;
	data->min_re = center_re - (center_re - data->min_re) * zoom_factor;
	data->max_re = center_re + (data->max_re - center_re) * zoom_factor;
	data->min_im = center_im - (center_im - data->min_im) * zoom_factor;
	data->max_im = center_im + (data->max_im - center_im) * zoom_factor;
}

void	zoom_in(t_data *data, double zoom_factor,
		double center_re, double center_im)
{
	data->zoom *= zoom_factor;
	data->min_re = center_re - (center_re - data->min_re) / zoom_factor;
	data->max_re = center_re + (data->max_re - center_re) / zoom_factor;
	data->min_im = center_im - (center_im - data->min_im) / zoom_factor;
	data->max_im = center_im + (data->max_im - center_im) / zoom_factor;
}

int	mouse_event(int button, int x, int y, t_data *data)
{
	double	zoom_factor;
	double	center_re;
	double	center_im;

	(void)x;
	/* Cast x to void to suppress unused parameter warning */

	(void)y;
	/* Cast y to void to suppress unused parameter warning */

	zoom_factor = 2.0;
	/* Set the zoom factor to 10% (1.1 times). This value provides a smooth zoom experience: 
	   not too fast, not too slow. It's a common choice in many applications for incremental zooming. */

	center_re = (data->min_re + data->max_re) / 2.0;
	/* Calculate the center of the real axis */

	center_im = (data->min_im + data->max_im) / 2.0;
	/* Calculate the center of the imaginary axis */

	if (button == 4)
	/* Check if scroll wheel moved up (zoom in) */
		zoom_in(data, zoom_factor, center_re, center_im);
		/* Call zoom_in function with calculated parameters */
	else if (button == 5)
	/* Check if scroll wheel moved down (zoom out) */
		zoom_out(data, zoom_factor, center_re, center_im);
		/* Call zoom_out function with calculated parameters */

	draw_fractal(data);
	/* Redraw the fractal with the updated zoom level */

	return (0);
	/* Return 0 to indicate successful execution */
}
