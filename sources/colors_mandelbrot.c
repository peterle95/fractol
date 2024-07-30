/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:54:25 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/23 13:03:13 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*This function determines the color of a pixel in the Mandelbrot set 
visualization based on how quickly the point (cr, ci) 
in the complex plane escapes the Mandelbrot set iteration.*/
int	color_mandelbrot(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	/*First, it calls mandelbrot(cr, ci), 
	which returns the number of iterations it took for 
	the point to escape (or MAX_ITERATIONS if it didn't escape).
	We count how many iterations it takes for |z| to exceed 2 	
	(which means the point will definitely escape to infinity), or until we reach MAX_ITERATIONS
	So besically all combinations of cr and ci which don't escape will 
	have the color set here*/
	if (iterations < MAX_ITERATIONS)
    return ((MAX_ITERATIONS - iterations) * 0xFFFFFF / MAX_ITERATIONS);
else
    return (0xFFFFFF);
	/*Now that it's working correctly, here's what's likely happening:
	a. For points inside the Mandelbrot set (reached MAX_ITERATIONS without escaping):
	
	These are colored white (0xFFFFFF)
	
	b. For points outside the Mandelbrot set:
	
	The color is determined by how quickly they escaped
	The formula is likely something like:
	color = (MAX_ITERATIONS - iterations) * 0xFFFFFF / MAX_ITERATIONS
	The Mandelbrot set itself (the main cardioid and bulbs) is white
	The area immediately surrounding the set is nearly black
	As you move further from the set, the colors become brighter
	The smooth gradients you see represent how quickly points escape
	
	
	Fractal Structure:
	
	The large white shapes are the main body of the Mandelbrot set
	The intricate patterns around the edges show where the behavior of points becomes chaotic
	Smaller white circles or bulbs attached to the main set are areas where the behavior stabilizes again
	
	
	Color Gradient:
	
	The gradient from dark to light as you move away from the set represents the "speed" at which points escape
	This creates a 3D-like effect, giving depth to the image
	
	
	Symmetry:
	
	The vertical symmetry you see is a fundamental property of the Mandelbrot set, due to the nature of complex number multiplication
	
	
	Detail and Complexity:
	
	The infinitely complex border between the set and the outside is what makes the Mandelbrot set a fractal
	You can zoom into any part of this border and find similar structures repeating at smaller and smaller scales*/
}

int	color_mandelbrot2(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	//return (iterations * 0x85a16a / MAX_ITERATIONS);
	if (iterations < MAX_ITERATIONS)
    return ((MAX_ITERATIONS - iterations) * 0x85a16a / MAX_ITERATIONS);
else
    return (0x85a16a);
}

int	color_mandelbrot3(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	//return (iterations * 0xffe9d7 / MAX_ITERATIONS);
	if (iterations < MAX_ITERATIONS)
    return ((MAX_ITERATIONS - iterations) * 0xffe9d7 / MAX_ITERATIONS);
else
    return (0xffe9d7);
}

int	color_mandelbrot4(double cr, double ci)
{
	int		iterations;

	iterations = mandelbrot(cr, ci);
	//return (iterations * 0xf0f8ff / MAX_ITERATIONS);
	if (iterations < MAX_ITERATIONS)
    return ((MAX_ITERATIONS - iterations) * 0xf0f8ff / MAX_ITERATIONS);
else
    return (0xf0f8ff);
}
