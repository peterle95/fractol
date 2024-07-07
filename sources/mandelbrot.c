/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:32 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/07 18:00:12 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mandelbrot(double cr, double ci)
{
	double	zr;
	double	zi;
	double	temp;
	int		n;

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

double	calculate_cr(t_data *data, int x)
{
	return (data->min_re + (double)x
		* (data->max_re - data->min_re) / WIN_WIDTH);
}

double	calculate_ci(t_data *data, int y)
{
	return (data->min_im + (double)y
		* (data->max_im - data->min_im) / WIN_HEIGHT);
}
