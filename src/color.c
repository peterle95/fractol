/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:49:57 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/09 22:01:08 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* color_shift_special:
	Extension of the color_shift function. Changes the color pattern.
	The fractal can then be rendered again with different color
	effects.
*/
static void	color_shift_special(t_fractol *fractal_data)
{
	int	alt_color;

	if (fractal_data->color == 0xFFFFFF)
		alt_color = 0xCCCCCC;
		/*Checks if the current color is pure white (0xFFFFFF).
		If so, sets a slightly darker shade (0xCCCCCC) 
		as alt_color for better contrast.*/
	else
		alt_color = fractal_data->color;
		/*Otherwise, uses the current color as alt_color.*/
	if (fractal_data->color_pattern == 5)
		set_color_contrasted(fractal_data, alt_color);
	else if (fractal_data->color_pattern == 6)
		set_color_opposites(fractal_data, fractal_data->color);
	else if (fractal_data->color_pattern == 7)
		set_color_graphic(fractal_data, fractal_data->color);
	else if (fractal_data->color_pattern == 8)
		set_color_multiple(fractal_data, (int [8]){0xFF0000, 0xFF7F00, 0xFFFF00,
			0x00FF00, 0x0000FF, 0x4B0082, 0x9400D3, 0xFFFFFF}, 8);
			/*predefined array of colors for a multi-colored pattern.
			It passes two arguments to set_color_multiple:
			fractal_data: 
			This is a pointer to the t_fractol structure, 
			which likely holds various data related to the fractal 
			rendering process, including the color palette.
			(int [8]){0xFF0000, 0xFF7F00, 0xFFFF00, ...}, 8: 
			This is an initializer for an integer array of size 8. 
			The array contains a set of predefined color values in hexadecimal 
			format (e.g., 0xFF0000 for red). The final argument 8 explicitly 
			specifies the size of the array.*/
}

/* color_shift_striped:
	Extension of the color_shift function. Changes the color pattern.
	The fractal can then be rendered again with different color
	effects.
*/
static void	color_shift_striped(t_fractol *fractal_data)
{
	if (fractal_data->color_pattern == 2)
		set_color_zebra(fractal_data, fractal_data->color);
	else if (fractal_data->color_pattern == 3)
		set_color_triad(fractal_data, fractal_data->color);
	else if (fractal_data->color_pattern == 4)
		set_color_tetra(fractal_data, fractal_data->color);
	else
		color_shift_special(fractal_data);
		/*color_shift_special already has access to color: 
		It receives a pointer to the t_fractol structure (fractal_data), 
		which contains the color member.
		color_shift_special has its own logic for determining or 
		adjusting colors based on context, further reducing the 
		need to explicitly pass a color argument.*/
}

/* color_shift:
	Reinitializes the MLX image and changes the color pattern.
	The fractal can then be rendered again with different color
	effects.

	Purpose:
	It updates the current color pattern index and reinitializes the 
	MLX image with the new color scheme, enabling dynamic color 
	shifting for the fractal rendering.

*/
void	color_shift(t_fractol *fractal_data)
{
	int	alt_color;

	fractal_data->color_pattern = (fractal_data->color_pattern + 1) % 9;
	/*This line advances the color_pattern to the next pattern by incrementing 
	it and using the modulo operator (%) to wrap it back to 0 if it reaches 9. 
	This ensures there are 9 possible color patterns that can be cycled through.*/
	reinit_img(fractal_data);
	/*This line calls the reinit_img function to clean up and re-create 
	the MLX image and color palette. This is necessary to apply the 
	new color scheme to the fractal rendering.*/
	if (fractal_data->color == 0x000000)
		alt_color = 0x333333;
		/*This block checks if the current main color is black (0x000000). 
		If so, it sets alt_color to a slightly lighter shade of gray 
		(0x333333) to avoid potential visibility issues with black backgrounds. 
		Otherwise, it keeps alt_color the same as the main color.*/
	else
		alt_color = fractal_data->color;
	if (fractal_data->color_pattern == 0)
		set_color_mono(fractal_data, alt_color);
		/*If the color_pattern is 0, it calls set_color_mono 
		to create a monochrome scheme using alt_color as the base color.*/
	else if (fractal_data->color_pattern == 1)
		set_color_multiple(fractal_data, (int [4]){0x000000, alt_color,
			get_percent_color(fractal_data->color, 50), 0xFFFFFF}, 4);
			/*If the color_pattern is 1, it calls set_color_multiple 
			with a predefined array of 4 colors (0x000000, alt_color, 
			a 50% lighter version of alt_color, and 0xFFFFFF) 
			to create a gradient effect.*/
	else
		color_shift_striped(fractal_data);
		/*If the color_pattern is anything else (2-8), 
		it calls color_shift_striped to handle those striped patterns.
		color_shift_striped already has access to color: 
		It receives a pointer to the t_fractol structure (fractal_data), 
		which contains the color member.
		color_shift_shift has its own logic for determining or 
		adjusting colors based on context, further reducing the 
		need to explicitly pass a color argument.*/
}
