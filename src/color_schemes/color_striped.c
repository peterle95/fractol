/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_striped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:50:04 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/10 13:47:42 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* fill_color:
	Sets a color for particular stripes intervals.
	If stripes = 2, the coloring will skip a palette iteration,
	if stripes = 3, the coloring will skip 2 palette iterations, and so on.
*/
static void	fill_color_stripe(t_fractol *fractal_data, int color, int stripe)
{	/*stripe: This is an integer representing 
	the spacing between stripes. It defines how many entries in the 
	palette will be skipped between applying the provided color.*/
	int	i;

	i = 0;
	while (i < MAX_ITERATIONS)
	{
		fractal_data->palette[i] = color;
		/*Inside the loop, the line fractal_data->palette[i] = color; 
		assigns the provided color value to the current palette entry 
		pointed to by i. This effectively sets the color for that specific 
		iteration step in the fractal calculation.*/
		i += stripe;
		/*The line i += stripe; increments the counter i by the value of stripe. 
		This effectively skips stripe - 1 entries in the palette before assigning 
		the color in the next iteration. This creates the striped pattern.*/
	}
	/*Let's say MAX_ITERATIONS is 256 (meaning the palette has 256 entries) and stripe is 2.
	The loop will iterate 256 times, filling the palette entries.
	In the first iteration (i = 0), fractal_data->palette[0] is assigned the color value.
	In the second iteration (i = 1), i is incremented by stripe 
	(2), making i equal to 3. So, fractal_data->palette[3] is assigned 
	the color (skipping entries 0, 1, and 2).
	This process continues, filling every other entry (0, 3, 6, ...) 
	with the provided color, creating a striped pattern with alternating colors.*/
}

/* get_percent_color:
	Calculates a color that is a certain percentage away
	from the provided color. Each color channel must be calculated
	separately. It does this for each color channel (red, green, and blue) independently.
	Intended to find somewhat complimentary colors.
	(For true complimentary colors picked from the color wheel,
	this function would need to be radically modified to use
	HSL colors rather than RGB...)
	Note: rgb[3] : rgb[0] = red, rgb[1] = green, rgb[2] = blue
*/
int	get_percent_color(int color, double percent)
{
	int		rgb[3];
	int		trgb[3];
	double	percentage;

	rgb[0] = (color >> 16) & 0xFF;
	/*This line extracts the red component from the provided color integer.
	Bitwise shifting (>> 16) moves the bits containing the red value 
	(usually the leftmost 8 bits) to the least significant position.
	The & 0xFF operation performs a bitwise AND with 255 
	(represented by 0xFF in hexadecimal). 
	This effectively isolates the red component by clearing all 
	bits except for the ones representing the red value.*/
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
	percentage = (percent / 100) * 256;
	/*This line calculates the offset value based on the provided percent.
	It divides the percent by 100 to get a value between 0 and 1.
	It then multiplies this value by 256 to get the offset amount 
	within the 0-255 range used for color channels.*/
	trgb[0] = (rgb[0] + percentage) - 256;
	/*This line calculates a new red value for the target color (trgb[0]).
	It adds the percentage offset to the original red value (rgb[0]).
	The - 256 is necessary because the offset could potentially 
	push the value outside the valid 0-255 range for color channels. 
	Subtracting 256 ensures the result stays within the valid range. 
	Similar calculations are done for green (trgb[1]) and blue (trgb[2]) channels.*/
	trgb[1] = (rgb[1] + percentage) - 256;
	trgb[2] = (rgb[2] + percentage) - 256;
	return (0xFF << 24 | trgb[0] << 16 | trgb[1] << 8 | trgb[2]);
	/*This line combines the adjusted red, green, and blue components 
	(trgb[0], trgb[1], trgb[2]) back into a single integer representing the new color.
	Bitwise shifting and OR operations are used to position 
	each component in its corresponding place within the 32-bit integer.
	0xFF << 24 sets the alpha channel (transparency) to fully opaque (255).
	trgb[0] << 16 shifts the adjusted red value 16 bits to the 
	left, positioning it in the red channel section of the integer.
	Similar shifts are done for green (<< 8) and blue (<< 0) 
	components to place them in their respective positions.*/
}



/*PURPOSE OF ZEBRA, TRIAD, TETRA:

	These functions create different striped color schemes for the fractal renderer. 
	They take a base color and generate variations of it to create distinct patterns 
	within the color palette.
	
  KEY POINTS:	
	All functions rely on the fill_color_stripe function (explained in a previous response) to create the striped patterns.
	The get_percent_color function is used to create secondary colors that are somewhat complementary to the base color.
	The last entry of the palette is often set to black, potentially for visual emphasis or to mark a specific iteration value in the fractal calculations.
*/


/* set_color_zebra:
	Sets a zebra-striped color scheme. Colors alternate between
	the given color and a complimentary color 50% away from the
	first.
*/
void	set_color_zebra(t_fractol *fractal_data, int color)
{
	int	color2;

	color2 = get_percent_color(color, 50);
	/*Calculates a second color (color2) that's 50% 
	away from the provided color using get_percent_color.*/
	fill_color_stripe(fractal_data, color, 1);
	fill_color_stripe(fractal_data, color2, 2);
	/*Fills alternating stripes in the palette with color and color2 
	using fill_color_stripe.*/
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
	/*Sets the last entry of the palette (MAX_ITERATIONS - 1) to black, for visual clarity.*/
}

/* set_color_triad:
	Sets a striped color scheme. Colors alternate between
	three colors: the given color, a color 33% away from the first
	and a color 66% away from the first.
*/
void	set_color_triad(t_fractol *fractal_data, int color)
{
	int		triad[2];

	triad[0] = get_percent_color(color, 33);
	triad[1] = get_percent_color(color, 66);
	/*Calculates two additional colors (triad[0] and triad[1]) 
	that are 33% and 66% away from the provided color.*/
	fill_color_stripe(fractal_data, color, 1);
	fill_color_stripe(fractal_data, triad[0], 2);
	fill_color_stripe(fractal_data, triad[1], 3);
	/*Fills stripes with color, triad[0], and triad[1] using fill_color_stripe.*/
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
	/*Sets the last entry of the palette to black.*/
}

/* set_color_tetra:
	Sets a striped color scheme. Colors alternate between
	four colors: the given color, a color 25% away from it,
	a color 50% away from the first, and a color 75% away from
	the first.

	TETRA = FOUR COLORS!!!
*/
void	set_color_tetra(t_fractol *fractal_data, int color)
{
	int	tetra[3];

	tetra[0] = get_percent_color(color, 25);
	tetra[1] = get_percent_color(color, 50);
	tetra[2] = get_percent_color(color, 75);
	/*Calculates three additional colors (tetra[0], tetra[1], and tetra[2]) 
	that are 25%, 50%, and 75% away from the provided color.*/
	fill_color_stripe(fractal_data, color, 1);
	fill_color_stripe(fractal_data, tetra[0], 2);
	fill_color_stripe(fractal_data, tetra[1], 3);
	fill_color_stripe(fractal_data, tetra[2], 4);
	/*Fills stripes with color, tetra[0], tetra[1], and tetra[2] using fill_color_stripe.*/
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
	/*Sets öast entry of the palette to black*/
}
