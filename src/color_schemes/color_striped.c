/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_striped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:50:04 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/09 22:19:22 by pmolzer          ###   ########.fr       */
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
	separately. Intended to find somewhat complimentary colors.
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
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
	percentage = (percent / 100) * 256;
	trgb[0] = (rgb[0] + percentage) - 256;
	trgb[1] = (rgb[1] + percentage) - 256;
	trgb[2] = (rgb[2] + percentage) - 256;
	return (0xFF << 24 | trgb[0] << 16 | trgb[1] << 8 | trgb[2]);
}

/* set_color_zebra:
	Sets a zebra-striped color scheme. Colors alternate between
	the given color and a complimentary color 50% away from the
	first.
*/
void	set_color_zebra(t_fractol *fractal_data, int color)
{
	int	color2;

	color2 = get_percent_color(color, 50);
	fill_color_stripe(fractal_data, color, 1);
	fill_color_stripe(fractal_data, color2, 2);
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
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
	fill_color_stripe(fractal_data, color, 1);
	fill_color_stripe(fractal_data, triad[0], 2);
	fill_color_stripe(fractal_data, triad[1], 3);
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

/* set_color_tetra:
	Sets a striped color scheme. Colors alternate between
	four colors: the given color, a color 25% away from it,
	a color 50% away from the first, and a color 75% away from
	the first.
*/
void	set_color_tetra(t_fractol *fractal_data, int color)
{
	int	tetra[3];

	tetra[0] = get_percent_color(color, 25);
	tetra[1] = get_percent_color(color, 50);
	tetra[2] = get_percent_color(color, 75);
	fill_color_stripe(fractal_data, color, 1);
	fill_color_stripe(fractal_data, tetra[0], 2);
	fill_color_stripe(fractal_data, tetra[1], 3);
	fill_color_stripe(fractal_data, tetra[2], 4);
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}
