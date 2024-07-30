/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:32 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/23 12:57:35 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*EXAMPLE:
 We'll assume some values for our fractal view and window size, 
 then calculate the complex number for the pixel (20, 2), and finally determine its color.

Assumptions:
- Window size: WIN_WIDTH = 800, WIN_HEIGHT = 600
- Fractal view: min_re = -2.0, max_re = 1.0, min_im = -1.5, max_im = 1.5

Step 1: Calculate cr (real part)

cr = min_re + (double)x * (max_re - min_re) / WIN_WIDTH
cr = -2.0 + (double)20 * (1.0 - (-2.0)) / 800
cr = -2.0 + 20 * 3.0 / 800
cr = -2.0 + 0.075
cr = -1.925

Step 2: Calculate ci (imaginary part)

ci = min_im + (double)y * (max_im - min_im) / WIN_HEIGHT
ci = -1.5 + (double)2 * (1.5 - (-1.5)) / 600
ci = -1.5 + 2 * 3.0 / 600
ci = -1.5 + 0.01
ci = -1.49


So, the pixel (20, 2) corresponds to the complex number (-1.925 - 1.49i).

Step 3: Determine the color

Now we need to use this complex number in the Mandelbrot set formula: z_n+1 = z_n^2 + c, 
where c is our complex number (-1.925 - 1.49i) and we start with z_0 = 0.

We iterate this formula until either |z| > 2 (the point escapes) or we reach 
the maximum number of iterations (let's say MAX_ITERATIONS = 100).

Let's do a few iterations:

1. z_1 = 0^2 + (-1.925 - 1.49i) = -1.925 - 1.49i
2. z_2 = (-1.925 - 1.49i)^2 + (-1.925 - 1.49i) = 1.4656 + 1.7345i
3. z_3 = (1.4656 + 1.7345i)^2 + (-1.925 - 1.49i) = -1.7729 + 3.5746i

At this point, |z_3| = sqrt((-1.7729)^2 + 3.5746^2) ≈ 3.98, which is > 2.
So this point escaped on the 3rd iteration.

Step 4: Assign a color

The color is typically assigned based on how quickly the point escapes. A common formula is:

color = iteration_count * 0xFFFFFF / MAX_ITERATIONS


In our case:
color = 3 * 0xFFFFFF / 100 = 0x0004C4C4

This color is a very dark cyan.

Final result:
The pixel at (20, 2) in the window represents the complex number (-1.925 - 1.49i) 
in the Mandelbrot set. This point escapes after 3 iterations, resulting in a very dark cyan color (0x0004C4C4).

This process is repeated for every pixel in the window to create the complete 
Mandelbrot set image. Points that never escape (within MAX_ITERATIONS) are 
typically colored black, forming the characteristic shape of the Mandelbrot set.
*/

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
		/*data->min_re: The minimum real value in the complex plane you're visualizing.
		  data->max_re: The maximum real value in the complex plane.
		  WIN_WIDTH: The width of your window in pixels.
		  x: The x-coordinate of the pixel (0 at left, WIN_WIDTH-1 at right).
		  
		  The formula performs a linear interpolation:
		  
		  It maps the pixel range [0, WIN_WIDTH] to the complex plane range [min_re, max_re].
		  (double)x / WIN_WIDTH gives the fraction of the way across the window.
		  Multiplying this by (max_re - min_re) scales it to the range in the complex plane.
		  Adding min_re shifts it to the correct starting point.
		  
		  Key points:

		  These functions enable zooming and panning:
		  By changing min_re, max_re, min_im, and max_im, you can zoom in/out or move around the complex plane.
		  
		  They maintain aspect ratio:
		  The ratio of (max_re - min_re) to (max_im - min_im) should match the window's aspect ratio to avoid distortion.
		  
		  Y-axis inversion:
		  Note that in most computer graphics, y increases downwards, while in math, 
		  y increases upwards. This function automatically handles this inversion.
		  
		  Precision:
		  Using double ensures high precision, which is crucial for deep zooms into the fractal.
		  */
}

double	calculate_ci(t_data *data, int y)
{
	return (data->min_im + (double)y
		* (data->max_im - data->min_im) / WIN_HEIGHT);
}
