/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:27 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/13 14:24:04 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Let's say we're testing the point z = 0.5 + 0.5i with the Julia set constant c = -0.7 + 0.27i.

So our initial values are:
zr = 0.5
zi = 0.5
cr = -0.7
ci = 0.27

Let's go through a few iterations:

Iteration 0 (start):
zr = 0.5
zi = 0.5
zr2 = 0.5 * 0.5 = 0.25
zi2 = 0.5 * 0.5 = 0.25
n = 0

Check loop condition: 0.25 + 0.25 = 0.5, which is <= 4.0, so we continue.

Iteration 1:
zi = 2 * 0.5 * 0.5 + 0.27 = 0.77
zr = 0.25 - 0.25 + (-0.7) = -0.7
zr2 = (-0.7) * (-0.7) = 0.49
zi2 = 0.77 * 0.77 = 0.5929
n = 1

Check loop condition: 0.49 + 0.5929 = 1.0829, which is <= 4.0, so we continue.

Iteration 2:
zi = 2 * (-0.7) * 0.77 + 0.27 = -0.805
zr = 0.49 - 0.5929 + (-0.7) = -0.8029
zr2 = (-0.8029) * (-0.8029) = 0.6446
zi2 = (-0.805) * (-0.805) = 0.6480
n = 2

Check loop condition: 0.6446 + 0.6480 = 1.2926, which is <= 4.0, so we continue.

We would continue this process until either:
1. The sum zr2 + zi2 exceeds 4.0, or
2. We reach MAX_ITERATIONS

Let's say we continue for a few more iterations and find that it escapes on the 7th iteration (n = 6). The function would then return 6.

In a typical Julia set visualization:
- Points that never escape (reach MAX_ITERATIONS) are considered part of the Julia set and might be colored black.
- Points that do escape are colored based on how quickly they escape. The value returned by this function (n) would be used to determine the color.

For example:
- If n is low (quick escape), it might be colored with a "cool" color like blue.
- If n is high (slow escape), it might be colored with a "warm" color like red.
- Values in between would get intermediate colors, creating a smooth gradient.

This process is repeated for many, many points across a grid, resulting in the beautiful, intricate patterns characteristic of the Julia set.*/

int	julia(double zr, double zi, double cr, double ci)
{
	double	zr2;
	double	zi2;
	int		n;

	zr2 = zr * zr;
	zi2 = zi * zi;
	/*zr2 and zi2 are pre-computed squares of zr and zi. This optimization saves repeated calculations in the loop.*/
	n = 0;
	while (zr2 + zi2 <= 4.0 && n < MAX_ITERATIONS)
	/*The sum of squares (zr2 + zi2) is less than or equal to 4. 
	This is equivalent to checking if the absolute value of the complex number is less than or equal to 2.*/
	{
		zi = 2 * zr * zi + ci;
		zr = zr2 - zi2 + cr;
		zr2 = zr * zr;
		zi2 = zi * zi;
		/*Let's derive these equations step by step. 
		This derivation comes from the complex function f(z) = z² + c, where z and c are complex numbers.

		1. Starting point:
		   Let z = a + bi (where a is the real part and b is the imaginary part)
		   Let c = cr + ci*i (where cr is the real part and ci is the imaginary part)
		
		2. The function we're iterating:
		   f(z) = z² + c
		
		3. Expanding z²:
		   z² = (a + bi)² = a² - b² + 2abi
		
		4. Adding c:
		   z² + c = (a² - b² + cr) + (2ab + ci)i
		
		5. For the next iteration, this result becomes our new z:
		   new_a = a² - b² + cr
		   new_b = 2ab + ci
		
		6. In our code:
		   - a is represented by zr (real part of z)
		   - b is represented by zi (imaginary part of z)
		   - a² is pre-computed as zr2
		   - b² is pre-computed as zi2
		
		7. Therefore, our equations become:
		   new_zi = 2 * zr * zi + ci
		   new_zr = zr2 - zi2 + cr
		
		8. After calculating the new values, we update zr2 and zi2 for the next iteration:
		   zr2 = new_zr * new_zr
		   zi2 = new_zi * new_zi
		
		And that's how we arrive at the code:
		
		zi = 2 * zr * zi + ci;  // new imaginary part
		zr = zr2 - zi2 + cr;    // new real part
		zr2 = zr * zr;          // update squared real part
		zi2 = zi * zi;          // update squared imaginary part*/
		n++;
	}
	return (n);
}

double	calculate_zr(t_data *data, int x)
{
	return (data->min_re + (double)x
		* (data->max_re - data->min_re) / WINDOW_WIDTH);
}

double	calculate_zi(t_data *data, int y)
{
	return (data->min_im + (double)y
		* (data->max_im - data->min_im) / WINDOW_HEIGHT);
}


/*The Mandelbrot set and Julia sets are closely related fractals, 
but they have some key differences. Let's break this down:

1. Formula:
   Both use the same basic formula: f(z) = z² + c, where z and c are complex numbers.

2. What varies:
   - Mandelbrot set: c varies, z starts at 0 <--------
   - Julia set: c is fixed, z varies		 <--------

3. Definition:
   - Mandelbrot set: The set of c values for which the orbit of 0 under f(z) = z² + c remains bounded.
   - Julia set: For a fixed c, the set of z values for which the orbit of z under f(z) = z² + c remains bounded.

4. Visualization:
   - Mandelbrot set: A single, universal set in the complex plane.
   - Julia sets: There's a different Julia set for each complex constant c.

5. Relationship:
   Each point c in the Mandelbrot set corresponds to a connected Julia set. Points outside the
    Mandelbrot set correspond to disconnected Julia sets.

6. Shape:
   - Mandelbrot set: Has a characteristic cardioid shape with bulbs attached.
   - Julia sets: Can have various shapes - connected, disconnected, or even totally scattered ("dust").

7. Exploration:
   - Mandelbrot set: Exploring means looking at different areas of the single set.
   - Julia sets: Exploring often involves changing the c value to see different sets.

8. Implementation difference:
   In the code, the main difference would be:
   - Mandelbrot: c is derived from the pixel coordinates, z starts at (0,0)
   - Julia: z is derived from the pixel coordinates, c is a fixed value
*/