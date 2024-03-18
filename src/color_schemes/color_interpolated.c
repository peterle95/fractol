/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_interpolated.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:53:17 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/18 17:55:39 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* interpolate:
	Interpolates between two hex colors. Each color channel must be
	calculated separately according to the formula:
		(endValue - startValue) * stepNumber / lastStepNumber + startValue
	The fractional component (stepNumber / lastStepNumber) must be provided
	as fraction parameter of this function.
	Note: rgb[3] : [0] = red, [1] = green, [2] = blue
*/
static int	interpolate(int startcolor, int endcolor, double fraction)
{
	int	start_rgb[3];
	int	end_rgb[3];

	start_rgb[0] = ((startcolor >> 16) & 0xFF);
	start_rgb[1] = ((startcolor >> 8) & 0xFF);
	start_rgb[2] = ((startcolor >> 0) & 0xFF);
	/*This line extracts the red component from the startcolor integer.
	Bitwise shifting (>> 16) moves the bits containing the red value (usually the leftmost 8 bits) 
	to the least significant position.
	The & 0xFF operation performs a bitwise AND with 255 (represented by 0xFF in hexadecimal). 
	This effectively isolates the red component by clearing all bits except for the ones representing 
	the red value. Similar operations are done for green (start_rgb[1]) and blue (start_rgb[2]) c
	omponents using >> 8 and >> 0 shifts respectively.
	Now, the start_rgb array holds the individual red, green, and blue values for the starting color. */
	end_rgb[0] = ((endcolor >> 16) & 0xFF);
	end_rgb[1] = ((endcolor >> 8) & 0xFF);
	end_rgb[2] = ((endcolor >> 0) & 0xFF);
	/*	The same process is repeated for the endcolor, storing its components in the end_rgb array.*/
	start_rgb[0] = (end_rgb[0] - start_rgb[0]) * fraction + start_rgb[0];
	/*This line calculates the interpolated value for the red component.
	Let's break it down:
	(end_rgb[0] - start_rgb[0]): 
	This calculates the difference between the red component of the end color and the red component of the start color.
	* fraction: 
	This multiplies the difference by the fraction value (between 0 and 1). 
	The fraction essentially determines how much of the difference to use for the interpolation.
		If fraction is 0, the result will be 0, meaning no change from the starting red value.
		If fraction is 1, the result will be the entire difference, effectively reaching the end color's red value.
	+ start_rgb[0]: 
	Finally, it adds the calculated difference (scaled by fraction) back to the starting red value. 
	This positions the result somewhere between the start and end red values based on the fraction.*/
	start_rgb[1] = (end_rgb[1] - start_rgb[1]) * fraction + start_rgb[1];
	start_rgb[2] = (end_rgb[2] - start_rgb[2]) * fraction + start_rgb[2];
	/*Similar calculations are done for the green (start_rgb[1]) 
	and blue (start_rgb[2]) components using the same approach.*/
	return (0xFF << 24 | start_rgb[0] << 16 | start_rgb[1] << 8 | start_rgb[2]);
	/*This line combines the interpolated red, green, and blue components 
	back into a single integer representing the new color.
	Bitwise shifting and OR operations are used to position 
	each component in its corresponding place within the 32-bit integer.
	0xFF << 24 sets the alpha channel (transparency) to fully opaque (255).
	start_rgb[0] << 16 shifts the interpolated red value 16 bits to the left,
	positioning it in the red channel section of the integer.
	Similar shifts are done for green (<< 8) and blue (<< 0) components 
	to place them in their respective positions.*/
}

/* set_color_mono:
	Sets a monochromatic color scheme. Colors range from
	black to the provided color, to white near the fractal
	border.
*/
void	set_color_mono(t_fractol *fractal_data, int color)
{
	int		i; // Loop counter for iterating through rows of the color palette (fractal_data->palette).
	int		j; // Loop counter for iterating through columns within a row of the palette.
	double	fraction; // Double variable to hold the interpolation value (between 0 and 1).
	int		color1; // Integer representing the starting color for interpolation in the current section.
	int		color2; // Integer representing the ending color for interpolation in the current section.

	color1 = 0x000000;// color1 is set to black (0x000000).
	color2 = color; // color2 is set to the provided color.
	i = 0;
	while (i < MAX_ITERATIONS)
	{/*Outer Loop (Rows):
		The loop iterates from i = 0 to i < MAX_ITERATIONS, filling each row of the color palette.*/
		j = 0;
		while (j < MAX_ITERATIONS / 2)
		{/*Inner Loop (Columns - Half Palette):
			The inner loop iterates from j = 0 to j < MAX_ITERATIONS / 2. 
			This fills only half of the palette entries in each row.
			The reason for filling half the palette is because the color 
			scheme transitions from black to the provided color in the first half 
			and then transitions from the provided color to white in the remaining half.*/
			fraction = (double)j / (MAX_ITERATIONS / 2);
			/*This calculates the interpolation factor fraction based on the current column position j.
			It divides j by MAX_ITERATIONS / 2 (which represents the number of 
			entries in half the palette). This ensures fraction goes 
			from 0 (at the beginning of the half-palette) to 1 (at the end of the half-palette).*/
			fractal_data->palette[i + j] = interpolate(color1, color2, fraction);
			/*This calls the interpolate function to get a new color 
			between color1 and color2 based on the calculated fraction.
			The result (interpolated color) is stored in the corresponding 
			palette entry (fractal_data->palette) at index i + j.*/
			j++;
		}
		color1 = color2; 
		/*After filling half the palette in the current row (j loop completes), 
		color1 is updated to color2 (which now holds the provided color).*/
		color2 = 0xFFFFFF;
		/*color2 is set to white (0xFFFFFF). 
		This prepares for the interpolation from the provided color 
		to white in the remaining half of the palette.*/
		i += j;
		/*This increments the row counter i by the number of columns (j) processed in the 
		inner loop. This ensures the outer loop moves to the next row in the palette for the next iteration.*/
	}
	fractal_data->palette[MAX_ITERATIONS -1] = 0;
	/*After both loops complete, the last entry of the palette 
	(MAX_ITERATIONS - 1) is explicitly set to black (0) for consistency.*/

	/* ------->  OVERALL, THIS FUNCTION CREATES A SMOOTH COLOR TRANSITION FROM
				BLACK TO THE PROVIDED COLOR AND THEN TO WHITE AT THE EDGE OF THE 
				FRACTAL VISUALIZATION*/
}

/* set_color_multiple:
	Sets a multicolor color scheme. Colors range from the
	first color provided in the array to the last. The colors are
	interpolated for a smooth transition between each. It is possible
	to provide more than 4 colors by casting a larger array and specifying
	how many colors are included.
*/
void	set_color_multiple(t_fractol *fractal_data, int colors[4], int n)
{
	int		i; // Loop counter for iterating through the color palette entries (0 to MAX_ITERATIONS - 1
	int		j; 
	/*Loop counter for iterating within a section of the palette 
	dedicated to a color transition (0 to less than MAX_ITERATIONS / (n - 1)).*/
	int		x; // Index into the colors array to keep track of the current and next colors for interpolation.
	double	fraction; // Double value btw 0 and 1 used to determine amount of change between the current and next colors.

	i = 0;
	x = 0;
	while (i < MAX_ITERATIONS)
	{/*The outer loop (while (i < MAX_ITERATIONS)):
		iterates through all entries of the color palette (fractal_data->palette).*/
		j = 0;
		while ((i + j) < MAX_ITERATIONS && j < (MAX_ITERATIONS / (n - 1)))
		{/*Inner loop:
			handles filling a section of the palette with interpolated colors 
			between two consecutive entries from the colors array.
				The condition (i + j) < MAX_ITERATIONS ensures we don't go beyond the valid palette index.
				The condition j < (MAX_ITERATIONS / (n - 1)) limits the 
				j loop to a specific size based on the number of 
				colors (n). This ensures each color transition gets an appropriate number of palette entries.*/
			fraction = (double)j / (MAX_ITERATIONS / (n - 1));
			/*This calculates the fraction which represents the progress within the current color 
			transition section. It's a value between 0 (at the beginning of the section) and 
			1 (at the end of the section).*/
			fractal_data->palette[i + j] = interpolate(colors[x], colors[x + 1], fraction);
			/*This calls the interpolate function to get a new color between colors[x] (current color) 
			and colors[x + 1] (next color) based on the fraction. The result is stored in the 
			current palette entry (i + j).*/
			j++;
		}
		x++;
		i += j;
		/*After filling a section of the palette for the current color transition:
			This increments the x index to point to the next color in the colors array for the next transition.
			This updates the i loop counter by the number of entries (j) 
			filled in the current section. This effectively moves i to the 
			beginning of the next section in the palette.*/
	}
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
	/*The loop structure ensures that the entire palette is filled with interpolated 
	colors between consecutive colors from the colors array.
	After the loops, fractal_data->palette[MAX_ITERATIONS - 1] is explicitly set to 
	black (0) as done in other color scheme functions.
	
	Key Points:
	The number of colors (n) determines the number of color transitions within the palette.
	The MAX_ITERATIONS / (n - 1) calculation ensures each color transition 
	gets a roughly equal-sized section in the palette.
	The interpolate function provides smooth color blending between consecutive colors in the colors array.*/
}
