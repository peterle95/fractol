/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:46:53 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/13 17:29:05 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* set_pixel_color:
	Add a color to one pixel of the MLX image map.
	The MLX image is composed of 32 bits per pixel.
	Color ints are stored from right to left, here, and are in
	the form of 0xAARRGGBB. 8 bits encode each color component,
	Alpha (Transparency), Red, Green and Blue.
	Bit shifting:
		- BB >> 0   (0x000000BB)
		- GG >> 8   (0x0000GG00)
		- RR >> 16  (0x00RR0000)
		- AA >> 24  (0xAA000000)
*/
static void	set_pixel_color(t_fractol *fractal_data, int x, int y, int color)
{
		fractal_data->buf[x * 4 + y * WIDTH * 4] = color;
		/*The function uses bit shifting to extract each color component (8 bits each) 
		from the color integer and sets them in the corresponding positions 
		of the pixel data buffer (fractal_data->buf).
		color >> 0: Extracts the blue component (BB) and sets it at fractal_data->buf[x * 4 + y * WIDTH * 4].*/
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
		/*color >> 8: Extracts the green component (GG) and sets it at 
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 1]. (Shifted by 8 bits to move it to the correct position).
*/
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
		/*Similar operations are done for red (RR) and alpha (AA) components, 
		shifting them by 16 and 24 bits respectively and setting them in the appropriate 
		memory locations within the buffer*/
}

/* calculate_fractal:
	Picks the correct fractal calculation function depending
	on the current fractal set.
*/
static int	calculate_fractal(t_fractol *fractal_data, double pixel_real, double pixel_imaginary)
{
	int	nb_itarations;

	if (fractal_data->set == MANDELBROT)
		nb_itarations = mandelbrot(pixel_real, pixel_imaginary);
	else if (fractal_data->set == JULIA)
		nb_itarations = julia(f, pixel_real, pixel_imaginary);
	else if (fractal_data->set == BURNING_SHIP)
		nb_itarations = burning_ship(pixel_real, pixel_imaginary);
	else if (fractal_data->set == TRICORN)
		nb_itarations = tricorn(pixel_real, pixel_imaginary);
	else if (fractal_data->set == MANDELBOX)
		nb_itarations = mandelbox(f, pixel_real, pixel_imaginary);
	return (nb_itarations);
}

/* render:
	Iterates through each pixel of the window, translates the pixel's
	coordinates into a complex number to be able to calculate if that number
	is part of the fractal set or not.
	The number of iterations that complex number goes through before being
	rejected from the fractal set determines which color is applied to the pixel.
	Once all pixels have been assessed and added to the MLX image,
	this function displays the MLX image to the window.
*/
void	render(t_fractol *f)
{
	int		x;
	int		y;
	/*x and y: Integers used to iterate through each pixel's coordinates.*/
	double	pixel_real;
	double	pixel_imaginary;
	/*pixel_real and pi: Doubles to store the real and imaginary parts 
	of the complex number for each pixel.*/
	int		nb_itarations;
	/* Integer to store the number of iterations required for the complex number to be classified 
	within the fractal set (calculated by the calculate_fractal function)*/

	mlx_clear_window(fractal_data->mlx, f->win);
	/*clears any previous image displayed on the window.*/
	y = -1;
	while (++y < HEIGHT)
	{
		/*The outer loop iterates through each row (y) from top to bottom (0 to HEIGHT - 1).*/
		x = -1;
		while (++x < WIDTH)
		{/*The inner loop iterates through each column (x) from left to right (0 to WIDTH - 1).*/
			pixel_real = f->min_r + (double)x * (f->max_r - f->min_r) / WIDTH;
			/*This line calculates the real part (pixel_real) of the complex number for the current pixel.
			It uses linear interpolation based on the pixel's x-coordinate (x) to 
			determine a value between the minimum (f->min_r) and maximum (f->max_r) 
			real values defined for the fractal.*/
			pixel_imaginary = f->max_i + (double)y * (f->min_i - f->max_i) / HEIGHT;
			/*This line calculates the imaginary part (pixel_imaginary) of the complex number for the current pixel.
			Similar to the real part, it uses linear interpolation based on the pixel's y-coordinate 
			ù(y) to determine a value between the minimum (f->min_i) and maximum (f->max_i) imaginary 
			values defined for the fractal.*/
			nb_itarations = calculate_fractal(f, pixel_real, pixel_imaginary);
			/*This line calls the calculate_fractal function (not shown in this code snippet). 
			This function likely implements the specific algorithm for the chosen fractal type 
			(e.g., Mandelbrot, Julia set) to determine how many iterations (nb_itarations) are needed 
			to classify the complex number (pixel_real, pixel_imaginary) as belonging to the fractal set or not.*/
			set_pixel_color(f, x, y, f->palette[nb_itarations]);
			/*This line sets the color of the current pixel (x, y) based on the number of iterations (nb_itarations).
			It uses the set_pixel_color function (not shown) to apply the color 
			from the palette (f->palette) at the index corresponding to the number of 
			iterations (nb_itarations). The palette likely defines a color scheme that visually 
			represents the number of iterations needed to classify a complex number within the fractal set.*/
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	/*After iterating through all pixels and setting their colors, the function calls mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);.
	This function displays the final image (f->img) on the window (f->win).*/
}
