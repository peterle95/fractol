/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:37:34 by mcombeau          #+#    #+#             */
/*   Updated: 2024/03/22 16:38:38 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* julia_shift:
*	Changes the Julia calculation kr and ki values to get a different Julia
*	fractal shape. This function should be called when the user clicks on
*	a point on the sceen.
*/
int	julia_shift(int x, int y, t_fractol *fractal_data)
{
	fractal_data->kr = fractal_data->min_r + (double)x * (fractal_data->max_r - fractal_data->min_r) / WIDTH;
	/*Updating kr (Real Component):

	This line calculates the new value for kr based on the 
	user's click position on the X-axis (x).
	fractal_data->min_r and fractal_data->max_r represent the minimum and maximum 
	real values of the current view in the complex number plane.
	(double)x: Casts the integer x (click position) 
	to a double for floating-point calculations.
	(fractal_data->max_r - fractal_data->min_r): This represents the width 
	of the view in the real number plane.
	WIDTH: This likely represents the width of the fractal window in pixels.
	The entire expression essentially performs a linear mapping:
	The X-axis of the window (0 to WIDTH) is mapped to the range of 
	real values in the current view (fractal_data->min_r to fractal_data->max_r).
	The click position x on the X-axis is used as a proportional 
	index to determine the corresponding real value within the view range.
	By adding this calculated value to fractal_data->min_r, the 
	function effectively sets kr to the real component at the 
	clicked point in the complex plane.*/
	fractal_data->ki = fractal_data->max_i + (double)y * (fractal_data->min_i - fractal_data->max_i) / HEIGHT;
	/*Updating ki (Imaginary Component):

	This line follows the same logic as for kr but for the 
	imaginary component (ki) based on the user's click position on the Y-axis (y).
	fractal_data->min_i and fractal_data->max_i represent the 
	minimum and maximum imaginary values of the current view.
	HEIGHT: This likely represents the height of the fractal window in pixels.
	The calculation performs a similar linear mapping 
	on the Y-axis to determine the imaginary 
	component (ki) at the clicked point based on y.*/
	render(fractal_data);
	/*This line calls the render function, likely responsible for 
	calculating and displaying the fractal on the screen. Since kr and ki have been updated, 
	the render function will use these new values to calculate a new iteration for each pixel, 
	resulting in a shift in the Julia fractal appearance based on the click position.*/
	return (0);
}

/* julia:
*	Checks whether a complex number is part of the Julia set or not.
*	Takes as parameters the real and imaginary coordinates of a point,
*	converted previously from a pixel's coordinates.
*	Returns the number of iterations before the number escapes 
*	the Julia set, which can then be used to determine coloring.
*/
int	julia(t_fractol *fractal_data, double zr, double zi)
{
	int		n;
	double	tmp;

	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zi * zi + zr * zr) > 4.0)
			break ;
		tmp = 2 * zr * zi + fractal_data->ki;
		zr = zr * zr - zi * zi + fractal_data->kr;
		zi = tmp;
		n++;
	}
	return (n);
}
/*
	How it works:

	The Julia set is closely related to the Mandelbrot set:
	its formula is identical. What differs are the complex
	number we plug into it.
	
	Mandelbrot uses 0 as a starting value for zr and zi, and
	adds pixel coordinates (cr and ci) every time it iterates.

	On the other hand, Julia starts with pixel coordinates as
	zr and zi and adds another complex number (kr and ki) every time
	it iterates.

	kr and ki values determine the shape Julia will take on.
	If kr + ki is part of the Mandelbrot set, Julia will be a continuous
	solid shape. If kr + ki is not part of the Mandelbrot set, the
	Julia fractal will be a disconnected set of separate islands.
	If kr + ki is a point that is close to the Mandelbrot fractal boundary,
	the same patterns we see at that point in the Mandelbrot fractal
	will emerge in the Julia fractal.
*/