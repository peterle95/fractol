/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:27 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/25 22:00:06 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Calculates the number of iterations for a given point in the Julia set
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

// Calculates the real component of a complex number based on the x-coordinate
double	calculate_zr(t_data *data, int x)
{
	return (data->min_re + (double)x
		* (data->max_re - data->min_re) / WINDOW_WIDTH);
}

// Calculates the imaginary component of 
// a complex number based on the y-coordinate
double	calculate_zi(t_data *data, int y)
{
	return (data->min_im + (double)y
		* (data->max_im - data->min_im) / WINDOW_HEIGHT);
}
