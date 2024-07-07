/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:54:25 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/06 20:55:29 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	color_mandelbrot(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}

int	color_mandelbrot2(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}

int	color_mandelbrot3(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}

int	color_mandelbrot4(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}
