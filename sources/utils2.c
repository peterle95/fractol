/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:37:22 by pmolzer           #+#    #+#             */
/*   Updated: 2024/09/03 15:16:14 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"


/*
Initial char pointer: The dst pointer is initially declared as a char * because we're doing byte-level 
arithmetic to calculate the exact memory address of the pixel. Characters (bytes) 
are the smallest addressable units in C, so using char * allows for precise byte-level control.
Casting to unsigned int: When setting the color, we cast dst to 
unsigned int * because colors are typically represented as 32-bit (4-byte) values in most graphics systems.
The reason we don't use unsigned int * from the beginning is that it 
could potentially cause alignment issues on some systems. By using char * for the 
arithmetic and then casting only when we set the value, we ensure that:

We can address any byte in memory (important for pixel-perfect operations).
We avoid potential alignment issues that could occur if we used unsigned int * for the arithmetic.
If we used unsigned int * from the start, on some systems, it might force alignment 
to 4-byte boundaries, which could lead to incorrect pixel addressing in certain scenarios.
 */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	/*A pointer to a character (dst) is declared. 
	This pointer will be used to calculate the address of the pixel in the image data.*/

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	/*This line calculates the address of the pixel to be modified:
	data->addr is the starting address of the pixel data in memory.
	y * data->line_length calculates the offset for the row based on the y-coordinate. 
		data->line_length is the number of bytes in a single row of pixels.
	x * (data->bits_per_pixel / 8) calculates the offset for the specific pixel in that row. 
		data->bits_per_pixel indicates how many bits are used for each pixel, so dividing by 8 converts it to bytes.
	The result is the address of the pixel in memory, which is assigned to dst.*/
	*(unsigned int *)dst = color;
	/*The syntax (unsigned int *) is a cast to an unsigned int pointer.
	This is necessary because the address of the pixel is of type char *.
	The cast allows us to treat the memory location as an unsigned int, which is
	what the mlx_pixel_put function is expecting.*/
	/*This line sets the color of the pixel at the calculated address:
	The dst pointer is cast to an unsigned int *, allowing us to treat the memory 
	location as an integer (which represents the color).
	The color value passed to the function is assigned to this memory location, 
	effectively changing the pixel's color.*/
}

// Validates if the input string is a valid Julia set parameter
int	validate_julia(char *str)
{
	int		i;
	int		digits_after_point;

	i = 0;
	digits_after_point = 0;
	while (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (1);
	i++;
	if (str[i] != '.')
		return (1);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		digits_after_point++;
		i++;
	}
	if (digits_after_point < 1 || digits_after_point > 3)
		return (1);
	return (0);
}
