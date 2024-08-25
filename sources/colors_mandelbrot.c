/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:54:25 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/25 22:01:31 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Calculates the color for the standard Mandelbrot set
int	color_mandelbrot(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	if (iterations < MAX_ITERATIONS)
		return ((MAX_ITERATIONS - iterations) * 0xFFFFFF / MAX_ITERATIONS);
	else
		return (0xFFFFFF);
}

// Calculates the color for the second Mandelbrot variation
int	color_mandelbrot2(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	if (iterations < MAX_ITERATIONS)
		return ((MAX_ITERATIONS - iterations) * 0x85a16a / MAX_ITERATIONS);
	else
		return (0xFFFFFF);
}

// Calculates the color for the third Mandelbrot variation
int	color_mandelbrot3(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	if (iterations < MAX_ITERATIONS)
		return ((MAX_ITERATIONS - iterations) * 0xffe9d7 / MAX_ITERATIONS);
	else
		return (0xFFFFFF);
}

// Calculates the color for the fourth Mandelbrot variation
int	color_mandelbrot4(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	if (iterations < MAX_ITERATIONS)
		return ((MAX_ITERATIONS - iterations) * 0xf0f8ff / MAX_ITERATIONS);
	else
		return (0xFFFFFF);
}
