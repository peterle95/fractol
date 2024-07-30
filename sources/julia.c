/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:27 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/23 12:58:04 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	julia(double zr, double zi, double cr, double ci)
{
	double	zr2;
	double	zi2;
	int		n;

	zr2 = zr * zr;
	zi2 = zi * zi;
	n = 0;
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

double	calculate_zr(t_data *data, int x)
{
	return (data->min_re + (double)x
		* (data->max_re - data->min_re) / WIN_WIDTH);
}

double	calculate_zi(t_data *data, int y)
{
	return (data->min_im + (double)y
		* (data->max_im - data->min_im) / WIN_HEIGHT);
}
