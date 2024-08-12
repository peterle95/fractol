/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:32 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/09 18:57:15 by pmolzer          ###   ########.fr       */
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
		/*This transition from the mathematical function to the code implementation involves some complex number 
		algebra and optimization. Let's break it down step-by-step.
		Starting with f(z) = z^2 + c, where z and c are complex numbers:
		
		Complex number representation:
			Let z = a + b*i and c = cr + ci*i; i^2 = -1
		Expanding f(z) = z^2 + c:
			f(z) = (a + b*i)^2 + (cr + ci*i)
		Expanding (a + b*i)^2:
			(a + bi)^2 = a^2 - b^2 + 2abi ---> Now, remember that i² = -1 (this is the fundamental definition of i) 
												So, (bi)² = b²(i²) = b²(-1) = -b²
		Substituting back into f(z):
			f(z) = a^2 - b^2 + 2abi + cr + ci*i
		Grouping real and imaginary parts:
			f(z) = (a^2 - b^2 + cr) + (2ab + ci)i
		
		Now, let's relate this to the code:
			temp = 2 * zr * zi + ci;
			zr = zr * zr - zi * zi + cr;
			zi = temp;
		Here, zr represents the real part (a) and zi represents the imaginary part (b) of z.
		
		zr = zr * zr - zi * zi + cr corresponds to the real part: [a^2 - b^2 + cr]
		temp = 2 * zr * zi + ci calculates the new imaginary part: [2ab + ci]
		*/
	}
	return (n);
	/*Let's iterate:

	Start: 
	zr = 0, zi = 0, n = 0
	cr = -0.4 (the real part of the complex number)
	ci = 0.6 (the imaginary part of the complex number)
	
	(|z|^2 =) 0^2 + 0^2 = 0 ≤ 4, so we continue.
	First iteration:
	temp = 2 * 0 * 0 + 0.6 = 0.6
	zr = 0^2 - 0^2 + (-0.4) = -0.4
	zi = 0.6
	n = 1
	
	(|z|^2 =) (-0.4)^2 + 0.6^2 = 0.16 + 0.36 = 0.52 ≤ 4, so we continue.
	Second iteration:
	temp = 2 * (-0.4) * 0.6 + 0.6 = 0.12
	zr = (-0.4)^2 - 0.6^2 + (-0.4) = 0.16 - 0.36 - 0.4 = -0.6
	zi = 0.12
	n = 2
	
	(|z|^2 =) (-0.6)^2 + 0.12^2 = 0.36 + 0.0144 = 0.3744 ≤ 4, so we continue.
	Third iteration:
	temp = 2 * (-0.6) * 0.12 + 0.6 = 0.456
	zr = (-0.6)^2 - 0.12^2 + (-0.4) = 0.36 - 0.0144 - 0.4 = -0.0544
	zi = 0.456
	n = 3
	
	(|z|^2 =) (-0.0544)^2 + 0.456^2 = 0.002959 + 0.207936 = 0.210895 ≤ 4, so we continue.
	
	This process continues until either:
	a) |z|^2 exceeds 4, in which case the function returns the number of iterations it took, or
	b) We reach MAX_ITERATIONS, in which case we assume the point is in the Mandelbrot set.
	For this particular point (-0.4 + 0.6i), the iterations will eventually cause |z|^2 to exceed 4, 
	and the function will return the number of iterations it took. This number is then typically used 
	to determine the color of the pixel representing this point in the complex plane.*/
}

double	calculate_cr(t_data *data, int x)
{
	return (data->min_re + (double)x
		* (data->max_re - data->min_re) / WIN_WIDTH);
		/*[]~(￣▽￣)~*[ FORMULA DERIVATION ]~(￣▽￣)~*
		Let's derive the formula step-by-step to understand how we arrive at this specific calculation.

		To derive this formula, we start with the goal of mapping a pixel's x-coordinate to a 
		point on the real axis of the complex plane. Here's the step-by-step process:
		
		1. Define the ranges:
		   - Screen space: 0 to WIN_WIDTH
		   - Complex plane (real axis): min_re to max_re
		
		2. We want to create a linear mapping between these two ranges. The general form of a linear mapping is:
		   y = mx + b
		   Where m is the slope and b is the y-intercept.

		   			Let's break it down further and 
					explain why we use a linear mapping in this context.

					Linear Mapping:
					A linear mapping is a way to convert values from one range to another in a straight-line 
					relationship. It's called "linear" because when graphed, it forms a straight line.
					
					The equation y = mx + b represents this straight line, where:
					- x is the input value (in our case, the pixel coordinate)
					- y is the output value (in our case, the position in the complex plane)
					- m is the slope (how steep the line is)
					- b is the y-intercept (where the line crosses the y-axis)
					
					Why use a linear mapping?
					In the context of rendering fractals:
					1. We have a screen with pixels (let's say 0 to 800 pixels wide).
					2. We want to map these pixels to a range in the complex plane (let's say from -2 to 2 on the real axis).
					
					We use a linear mapping because:
					1. It's simple and computationally efficient.
					2. It preserves proportions, so the fractal looks correct on screen.
					3. It allows for smooth zooming and panning.
					
					Example:
					Let's say we have a 800-pixel wide screen, and we want to map it to the range -2 to 2 in the complex plane.
					
					- The left edge of the screen (x = 0) should correspond to -2 in the complex plane.
					- The right edge (x = 800) should correspond to 2 in the complex plane.
					- The middle of the screen (x = 400) should correspond to 0 in the complex plane.
					
					A linear mapping ensures that this relationship holds true for every pixel in between, 
					creating a smooth and accurate representation of the fractal.
					
					In the next steps of the derivation, we calculate the specific m and b for our case, 
					which gives us the formula used in the code. The linear mapping allows us to precisely 
					determine which point in the complex plane each pixel represents.
							
		3. In our case:
		   - x is the pixel coordinate (0 to WIN_WIDTH)
		   - y is the real value in the complex plane (min_re to max_re)
		
		4. To find the slope (m), we use the formula:
		   m = (y2 - y1) / (x2 - x1)
		
		   In our context:
		   m = (max_re - min_re) / (WIN_WIDTH - 0)
		   m = (max_re - min_re) / WIN_WIDTH
		
		5. Now we have:
		   real_value = m * x + b
		
		   Where:
		   m = (max_re - min_re) / WIN_WIDTH
		   b = min_re (because when x = 0, we want real_value = min_re)
		
		6. Substituting these in:
		   real_value = ((max_re - min_re) / WIN_WIDTH) * x + min_re
		
		7. Rearranging for clarity:
		   real_value = min_re + (x * (max_re - min_re) / WIN_WIDTH)
		
		And this is exactly the formula we see in the code:
		
		```c
		return (data->min_re + (double)x * (data->max_re - data->min_re) / WIN_WIDTH);
		```
		
		The `(double)` cast ensures that the calculation is done in floating-point arithmetic for precision.
		
		This formula effectively maps each pixel's x-coordinate to a corresponding point on the real axis of the complex plane, allowing the program to render the fractal accurately across the window.
		
		
		  data->min_re: The minimum real value in the complex plane you're visualizing.
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
	/*Let's analyze the `calculate_ci` function, which is very similar to the `calculate_cr` 
	function we discussed earlier, but it works with the imaginary axis of the complex plane.

	Here's what `calculate_ci` does:
	1. Purpose: This function calculates the imaginary component of a complex number based on the y-coordinate of a pixel in the window.
	
	2. Formula breakdown:
	   ```c
	   return (data->min_im + (double)y * (data->max_im - data->min_im) / WIN_HEIGHT);
	   ```
	
	   - `data->min_im`: The minimum imaginary value in the complex plane being viewed.
	   - `data->max_im`: The maximum imaginary value in the complex plane being viewed.
	   - `(double)y`: The y-coordinate of the pixel, cast to a double for precise calculation.
	   - `WIN_HEIGHT`: The height of the window in pixels.
	
	3. How it works:
	   - It maps the y-coordinate (0 to WIN_HEIGHT) to the imaginary axis (min_im to max_im).
	   - When y = 0 (top of the screen), it returns `min_im`.
	   - When y = WIN_HEIGHT (bottom of the screen), it returns `max_im`.
	   				When y = 0 (top of the screen):
						result = data->min_im + (double)0 * (data->max_im - data->min_im) / WIN_HEIGHT
						Substituting y = 0 into the formula:
						Simplifying:
						result = data->min_im + 0
						result = data->min_im
					So when y = 0, the function returns min_im.
					When y = WIN_HEIGHT (bottom of the screen):
						Substituting y = WIN_HEIGHT into the formula:
						result = data->min_im + (double)WIN_HEIGHT * (data->max_im - data->min_im) / WIN_HEIGHT
						The WIN_HEIGHT terms cancel out:
						result = data->min_im + (data->max_im - data->min_im)
						Simplifying:
						result = data->max_im
					So when y = WIN_HEIGHT, the function returns max_im.
		- For y values in between, it linearly interpolates between min_im and max_im.
	
	4. Comparison with `calculate_cr`:
	   - `calculate_cr` maps x-coordinates to the real axis.
	   - `calculate_ci` maps y-coordinates to the imaginary axis.
	   - Together, they convert a pixel's (x, y) coordinates to a complex number (real, imaginary).
	
	5. Why it's important:
	   - In fractal rendering, each pixel represents a complex number.
	   - The real part comes from `calculate_cr`, the imaginary part from `calculate_ci`.
	   - This mapping allows the program to determine which point in the complex plane each pixel represents.
	
	6. Screen vs. Complex Plane orientation:
	   - Note that the y-axis is typically inverted: in screen coordinates, y increases downwards,
	    while in the complex plane, the imaginary axis increases upwards.
	   - This inversion is usually handled in how `min_im` and `max_im` are set up, often with `min_im` being the larger value.
	
	By using both `calculate_cr` and `calculate_ci`, the program can convert any pixel coordinate (x, y) 
	into a complex number (real, imaginary). This is crucial for determining the color of each pixel 
	when rendering fractals like the Mandelbrot set or Julia sets, as the fractal algorithms operate on these complex numbers.*/
}
