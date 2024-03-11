/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:50:15 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/11 15:45:05 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Notice: These color scheme functions were created purely by accident,
	and may not always work well with every color provided. They rely on
	pushing past FFFFFF or 000000 which can have some unpredictable results.
	
	When they do work, they	create very interesting and beautiful
	colorings, though, which is why they have not been cut from this
	project.

	Typically, they work well with middling colors, especially ones like:
		9966FF	33FF33	FF6666	CCCC00	CC6600
	
	But they don't work too well with edge colors like:
		000000	FFFFFF	00FF00	FF0000	0000FF	FFFF00

	COMMON STRUCTURE:

	All three functions follow a similar pattern:
	They extract the red, green, and blue components from the provided color.
	They iterate through the color palette (fractal_data->palette) up to MAX_ITERATIONS.
	Inside the loop, they manipulate the color components 
	using a specific approach for each function.
	They create a new color based on the adjusted components and set it in the palette.
	Finally, they set the last entry of the palette (MAX_ITERATIONS - 1) to black (0)
*/

#include "fractol.h"

void	set_color_opposites(t_fractol *fractal_data, int color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	/*Extracts the red component from the provided color integer using 
	bitwise shifting and masking.*/
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	/*Similar operations are done for g (green) and b (blue) components.*/
	i = -1;
	/*Initializes a loop counter i to -1 
	(because the loop increments it before the first iteration).*/
	while (++i < MAX_ITERATIONS)
	{
		fractal_data->palette[i] = 0;
		/*Before modifying the color for this iteration, 
		the function sets the corresponding palette entry to black (0).*/
		r += i % 0xFF;
		/*This line tries to create an opposite for the red component.
		It adds the modulo (%) of the iteration number (i) to the red value (r).
		The modulo ensures the result stays within the 0-255 range for valid color values.
		However, this simple addition might not always produce 
		true opposites, especially for colors that aren't "middling" 
		(neither very dark nor very light).*/
		g += i % 0xFF;
		b += i % 0xFF;
		/*Similar additions (g += i % 0xFF;, b += i % 0xFF;) 
		are done for green and blue components.*/
		fractal_data->palette[i] = 0xFF << 24 | r << 16 | g << 8 | b;
		/*This line combines the adjusted red, green, and blue components (r, g, b) back into a single integer representing the new color for this iteration.
		Bitwise shifting and OR operations are used to position each 
		component in its corresponding place within the 32-bit integer:
		0xFF << 24 sets the alpha channel (transparency) to fully opaque (255).
		r << 16 shifts the adjusted red value 16 bits to the left, 
		positioning it in the red channel section of the integer.
		Similar shifts are done for green (<< 8) and blue (<< 0) components.*/
	}
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
	/*After the loop completes, the function explicitly sets the last 
	entry of the palette (MAX_ITERATIONS - 1) to black (0). 
	This might be for consistency or to avoid unexpected behavior 
	when using the entire palette.*/
}

void	set_color_contrasted(t_fractol *fractal_data, int color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	/*Extracts the red component from the provided color integer using 
	bitwise shifting and masking.*/
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	/*Similar operations are done for g (green) and b (blue) components.*/
	i = -1;
	/*Initializes a loop counter i to -1 
	(because the loop increments it before the first iteration).*/
	while (++i < MAX_ITERATIONS)
	{
		fractal_data->palette[i] = 0;
		/* initializes the current palette entry to black (0) before potentially modifying it.*/
		if (r != 0xFF)
			r += i % 0xFF;
			/*Checks if the red component (r) is not 0xFF (white).
			If not white, it adds the modulo (%) of the iteration number (i) to r. 
			This modulo ensures the value stays within the 0-255 range.*/
		if (g != 0xFF)
			g += i % 0xFF;
		if (b != 0xFF)
			b += i % 0xFF;
			/*Similar conditional statements exist for green (g) and blue (b) components.*/
		fractal_data->palette[i] = 0xFF << 24 | r << 16 | g << 8 | b;
		/*This line combines the potentially adjusted red, green, and blue components (r, g, b) into a new color integer.
		Bitwise shifting and OR operations are used to position each component in its corresponding place within the 32-bit integer:
		0xFF << 24 sets the alpha channel (transparency) to fully opaque (255).
		r << 16 shifts the adjusted red value 16 bits to the left, positioning it in the red channel section of the integer.
		Similar shifts are done for green (<< 8) and blue (<< 0) components.
		This new color is then stored in the current palette entry (fractal_data->palette[i]).*/
	}
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
	/*fractal_data->palette[MAX_ITERATIONS - 1] = 0;
	After the loop completes, this line sets the last entry of the palette 
	(MAX_ITERATIONS - 1) to black (0). This might be used for consistency 
	or to avoid unexpected behavior at the end of the color gradient.*/
}



void	set_color_graphic(t_fractol *fractal_data, int color)
{
	int	i;
	int	rgb[3];

	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
	/*extracting red, green and blue*/
	i = -1;
	while (rgb[0] < 0x33 || rgb[1] < 0x33 || rgb[2] < 0x33)
	/*The code then enters a loop that continues as long as any of the red, green, 
	or blue components in rgb are below a certain threshold 
	(0x33, which is roughly equivalent to a dark shade of gray).*/
	{
		if (rgb[0] != 0xFF)
			rgb[0]++;
		if (rgb[1] != 0xFF)
			rgb[1]++;
		if (rgb[2] != 0xFF)
			rgb[2]++;
			/*Inside the loop, it checks each color component.
			If a component (rgb[0], rgb[1], or rgb[2]) is not already 
			at its maximum (0xFF), it increments that component by 1.*/
	/*This initial loop essentially darkens the starting colors if they 
	are not already dark enough. This step might not always be necessary 
	and could be commented out to see the effect without this pre-darkening.*/
	}
	while (++i < MAX_ITERATIONS)
	/*After the optional darkening step, the main loop iterates through the 
	color palette (fractal_data->palette) up to MAX_ITERATIONS.*/
	{
		fractal_data->palette[i] = 0;
		/*It sets the current palette entry to black (0).*/
		rgb[0] -= i % 0xFF;
		rgb[1] -= i % 0xFF;
		rgb[2] -= i % 0xFF;
		/*It subtracts the modulo (%) of the iteration number (i) from each color component in rgb.
		This subtraction can lead to negative values outside the valid 0-255 color range. 
		The code doesn't handle this explicitly, potentially resulting in unexpected colors.*/
		fractal_data->palette[i] = 0xFF << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2];
		/*It combines the adjusted color components back into a 
		single integer representing a new color.*/
	}
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
	/*Similar to other color scheme functions, the last entry of the
	 palette (MAX_ITERATIONS - 1) is explicitly set to black (0).*/
}


/*There are two possible reasons why the set_color_graphic function uses an 
int rgb[3] array to store the color components, while other functions 
use separate int r, int g, and int b variables:

Conciseness and Code Readability (for small color sets):

For functions that only deal with a single color value, 
using separate r, g, and b variables can make the code more readable. 
It explicitly separates the red, green, and blue components with clear 
variable names. This approach might be preferred when dealing with a 
small number of colors and clarity is a priority.
Potential Performance Optimization (for large color sets):

In scenarios where you're working with many colors or 
manipulating colors frequently, using an array like rgb[3] could 
offer slight performance benefits. This is because accessing elements 
within an array can be slightly faster than accessing individual variables, 
especially when dealing with large datasets.
However, the performance difference between these approaches is usually 
negligible for small color sets. In the context of these fractal 
renderer color scheme functions, where the number of colors being 
processed is likely limited, the choice between using an array or 
separate variables is more about readability and programmer preference.

Here's a table summarizing the potential advantages of each approach:

Approach			Advantages
Separate r, g, b	Improved code readability, especially for small sets
int rgb[3] array	Potentially faster for large color sets (micro-optimization)
*/
