/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:49:28 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/08 18:03:07 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* clean_init:
	Initializes the fractol data structure with default
	values to be replaced later. Used for error detection.
*/
void	clean_init(t_fractol *fractal_data)
{
	fractal_data->mlx = NULL;
	fractal_data->win = NULL;
	fractal_data->img = NULL;
	fractal_data->buf = NULL;
	/*Pointers and Memory Allocation: 
	These elements are likely pointers that will hold memory addresses for 
	different resources:

	mlx might point to a connection with the MiniLibX library.
	win might point to a specific window created with MiniLibX.
	img might point to a MiniLibX image object.
	buf might point to the raw image data buffer used to store pixel information.
	NULL as Placeholder for Unallocated Memory: In C, NULL is a special constant that represents the absence of a valid memory address. It essentially signifies that the pointer doesn't point to any allocated memory location yet.
	
	Reasons Not to Use 0 or -1:
	0 might be a valid memory address in some systems, so using it as a null 
	pointer indicator can lead to unexpected behavior.
	-1 is typically used to represent an error condit*/
	fractal_data->set = -1;
	/*Not NULL: Using NULL for an integer variable is generally not 
	recommended as it might lead to unintended behavior if not handled 
	carefully. Assigning NULL to an integer pointer wouldn't be a valid 
	comparison.
	Not 0: Setting it to 0 could be a possibility, but 0 is often used as 
	a valid value for the Mandelbrot set (since it's the center of the 
	complex plane typically displayed). Using -1 avoids any potential 
	conflicts with actual fractal set values.
	Negative Value: A negative value like -1 can be a convenient way to 
	signal an "unset" or "invalid" state. It's a common convention used 
	in programming to differentiate between a valid integer and the 
	absence of a specific value.*/
	fractal_data->min_r = 0;
	fractal_data->max_r = 0;
	fractal_data->min_i = 0;
	fractal_data->max_i = 0;
	fractal_data->kr = 0;
	fractal_data->ki = 0;
	fractal_data->sx = 0;
	fractal_data->rx = 0;
	fractal_data->fx = 0;
	/*There are two main reasons why these elements 
	(min_r, max_r, min_i, max_i, kr, ki, sx, rx, and fx) 
	are initialized to 0 in clean_init instead of NULL or other values:
	Data Type: 
	These variables are likely of numeric data types like double or float 
	which represent real numbers. Setting them to NULL wouldn't be 
	appropriate because NULL is typically used for pointers.
	Initial Viewing Area and Parameters:
	min_r, max_r, min_i, and max_i define the initial viewing area of the complex plane 
	to be explored for fractals. Setting them to 0 initially represents the 
	center point ((0, 0)) on the complex plane. This is a common starting 
	point for exploring many fractal sets like Mandelbrot and Julia.
	kr and ki are specific to the Julia set calculation. When no Julia set is selected 
	(set is -1), initializing them to 0 ensures no initial offset is applied.
	sx is likely a scaling factor for the viewing area. 0 might be a placeholder or 
	indicate no initial scaling is applied.
	rx and fx are parameters used in the Mandelbox calculation. Since Mandelbox 
	isn't selected initially, 0 ensures these parameters are not set prematurely.*/
	fractal_data->palette = NULL;
	/*NULL bc palette is a pointer*/
	fractal_data->color_pattern = -1;
	/*fractal_data->color_pattern could be initialized to other values 
	like 0 or a dedicated NULL value constant. 
	Here's why using -1 might be a design choice:
	Distinguishing between "unset" and valid values: 
	Numbers starting from 0 are often used to represent valid 
	indices or patterns. Using -1 clearly separates the "unset" state 
	from potentially valid color pattern options. 
	This can be helpful for checks and logic within the code.
	Avoiding conflicts with potential future color pattern values: 
	If the color pattern options start from 0 and increment upwards, 
	using 0 for "unset" might conflict with a legitimate color pattern 
	option introduced later. Using -1 avoids this potential issue.
	Leveraging the signed integer nature: 
	In some cases, the code might involve calculations or 
	comparisons with the color_pattern value. Using a 
	negative value like -1 can make it easier to distinguish 
	it from non-negative pattern indices during such operations.
	
	fractal_data->color_pattern = (fractal_data->color_pattern + 1) % 9;
	--> this defines the color_pattern to 0
	
	*/
	fractal_data->color = 0;
	/*In many computer graphics systems, color values are often represented 
	as integers where each byte represents a color channel 
	(red, green, and blue).
	Setting the color to 0 (in decimal notation) typically translates to 
	black because:
	In binary, 0 represents the off state for each color channel 
	(red, green, blue).
	With all channels off, the resulting color is black.
	Therefore, initializing fractal_data->color to 0 makes sense as a 
	default starting point for the image color. It sets all color 
	channels to off, resulting in a black canvas before the fractal is drawn.

	Value	Reason unsuitable
	-1		Negative values are typically not used for color representation in this context.
	NULL	NULL is usually used for pointers, not color values.*/
}

/* get_complex_layout:
	Maps the complex number axes to the window width and height to
	create an equivalence between a given pixel and a complex number.
		- The Mandelbox set real and imaginary axes range from 4 to -4
		so the edges are mapped to those numbers for the fractal to appear
		centered.
		- Julia needs a bit more space to the right than Mandelbrot or
		Burning Ship, so the mapping must also be shifted slightly.
	Also, one of the edges is always calculated according to the other edges
	to avoid fractal distortion if the window proportions change.

	Purpose:

	This function establishes a mapping between pixels on the screen and complex numbers in the complex plane. 
	This mapping determines which complex number corresponds to each pixel when rendering the fractal.
*/
void	get_complex_layout(t_fractol *fractal_data)
{
	if (fractal_data->set == MANDELBOX)
	{
		fractal_data->min_r = -4.0;
		fractal_data->max_r = 4.0;
		/*Sets min_r and max_r to -4.0 and 4.0, respectively, to cover 
		the standard viewing area for the Mandelbox set.*/
		fractal_data->min_i = -4.0;
		fractal_data->max_i = fractal_data->min_i + (fractal_data->max_r - fractal_data->min_r) * HEIGHT / WIDTH;
		/*Sets min_i based on max_i. The calculation ensures that the imaginary axis (i) 
		scales proportionally to the real axis (r) based on the window's width and height 
		(WIDTH and HEIGHT). 
		This keeps the aspect ratio consistent even if the window is resized.*/
	}
	else if (fractal_data->set == JULIA)
	{
		fractal_data->min_r = -2.0;
		fractal_data->max_r = 2.0;
		/*Sets min_r and max_r to -2.0 and 2.0, respectively, for a slightly 
		wider viewing area compared to Mandelbox or Burning Ship 
		(potentially to accommodate the Julia set's characteristics).*/
		fractal_data->min_i = -2.0;
		fractal_data->max_i = fractal_data->min_i + (fractal_data->max_r - fractal_data->min_r) * HEIGHT / WIDTH;
	}
	else // (default)
	{
		fractal_data->min_r = -2.0;
		fractal_data->max_r = 1.0;
		fractal_data->max_i = -1.5;
		fractal_data->min_i = fractal_data->max_i + (fractal_data->max_r - fractal_data->min_r) * HEIGHT / WIDTH;
		/*Sets min_r, max_r, min_i, and max_i to values suitable for a generic fractal 
		display (likely centered around the origin). 
		The calculation for min_i again ensures proper aspect ratio.*/
	}
	/*This approach ensures that the displayed fractal covers a consistent and appropriate 
	region of the complex plane based on the chosen fractal type and the window dimensions.
	
	min_r (minimum real part): 
	This defines the leftmost edge of the visible area on the real number (x-axis) plane of the complex plane.

	max_r (maximum real part):
	This defines the rightmost edge of the visible area on the real number plane.
	
	min_i (minimum imaginary part):
	This defines the bottommost edge of the visible area on the imaginary number (y-axis) 
	plane of the complex plane.
	
	max_i (maximum imaginary part):
	This defines the topmost edge of the visible area on the imaginary number plane.
	
	By setting these values, the function essentially creates a rectangular 
	viewport within the complex plane that will be used for calculations 
	during fractal rendering. The specific values chosen depend on the selected 
	fractal type (fractal_data->set).
	*/
}

/* init_img:
	Initializes an MLX image and a color palette. The color palette will
	be used to store every shade of color for every iteration number,
	and the color of each pixel will be stored in the image, which will
	then be displayed in the program window.

	This function initializes two crucial elements for rendering fractals:

	Color Palette:
	It creates a color palette to store color information for each iteration step
	(up to MAX_ITERATIONS). Each entry in the palette will likely hold an integer 
	representing a specific color.
	MLX Image:
	It creates an MLX image using the provided mlx instance (fractal_data->mlx). 
	This image will be used as a canvas to store the calculated colors for each pixel, 
	ultimately representing the rendered fractal on the screen.
*/
static void	init_img(t_fractol *fractal_data)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buf;

	fractal_data->palette = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	/*This line allocates memory for the color palette using ft_calloc. 
	ft_calloc is likely a custom function that allocates memory and initializes 
	it to zero, ensuring a clean starting state for the palette.
	The size of the allocated memory is calculated as (MAX_ITERATIONS + 1) * sizeof(int). 
	This allocates enough space to store an integer value (representing color) for 
	each iteration step (from 0 to MAX_ITERATIONS) plus one extra element (possibly 
	for a special case or default color).*/
	if (!(fractal_data->palette))
		clean_exit(msg("error initializing color scheme.", "", 1), fractal_data);
	fractal_data->img = mlx_new_image(fractal_data->mlx, WIDTH, HEIGHT);
	/*This line creates a new MLX image using mlx_new_image. It takes three arguments:
	fractal_data->mlx: 
	This is a pointer to the MLX instance, likely created earlier 
	during program initialization. MLX is a library for creating graphical user interfaces.
	WIDTH: This is a pre-defined constant representing the width of the image in pixels.
	HEIGHT: This is another pre-defined constant representing the height of the image in pixels.
	The return value of mlx_new_image is stored in fractal_data->img. 
	If image creation fails, fractal_data->img will be NULL.*/
	if (!(fractal_data->img))
		clean_exit(msg("image creation error.", "", 1), fractal_data);
	buf = mlx_get_data_addr(fractal_data->img, &pixel_bits, &line_bytes, &endian);
	/*This line retrieves information about the created MLX image using mlx_get_data_addr. It takes four arguments and stores the results in variables:
	fractal_data->img: 
	This is the image we just created.
	&pixel_bits: 
	This is a pointer to an integer variable where mlx_get_data_addr will store 
	the number of bits per pixel in the image.
	&line_bytes: 
	This is a pointer to an integer variable where mlx_get_data_addr will store 
	the number of bytes required to represent a single line of pixels in the image. 
	This is relevant for efficient memory access.
	&endian: 
	This is a pointer to an integer variable where mlx_get_data_addr will store the 
	endianness of the image (whether it's little-endian or big-endian). 
	Endianness determines the order of bytes within a multi-byte value.
	The return value of mlx_get_data_addr is stored in a variable named buf. This buf variable points to the raw data buffer of the image where we can directly manipulate pixel colors.*/
	fractal_data->buf = buf;
	/*This line stores the retrieved image data buffer pointer (buf) in the 
	fractal_data structure. This pointer will be crucial for later functions 
	that manipulate pixel colors within the image during the fractal calculation 
	and rendering process.*/
}

/* reinit_image:
	Cleanly reinitializes the MLX image if the color palette or 
	fractal type is modified at runtime.
*/
void	reinit_img(t_fractol *fractal_data)
{
	if (fractal_data->mlx && fractal_data->img)
		mlx_destroy_image(fractal_data->mlx, fractal_data->img);
	if (fractal_data->palette)
		free(fractal_data->palette);
	if (fractal_data->buf)
		fractal_data->buf = NULL;
	init_img(fractal_data);
}

/* init:
	Creates a new MLX instance, a new window and populates
	the fractol data structure with default values.
*/
void	init(t_fractol *fracta l_data)
{
	fractal_data->mlx = mlx_init();
	if (!fractal_data->mlx)
		clean_exit(msg("MLX: error connecting to mlx.", "", 1), fractal_data);
		/*If there's an error, the function calls clean_exit with an appropriate error message 
		using the msg function. The clean_exit function handles error 
		cleanup and exits the program.
		Breakdown:
		clean_exit: 
		Function to clean up resources and exit with a specific code.
		msg(...): 
		Function call (explained below) to construct an error message.
		"MLX: error creating window.":
		 Error message to be displayed.
		"": 
		----> Empty string, likely serving as a placeholder or separator.
		Including an empty string ("") as an argument is a way to handle optional 
		arguments within a function. Even though it doesn't provide any additional 
		information, it keeps the function call consistent with its definition, 
		which might expect three arguments.
		1: 
		Error code representing the specific error type (window creation failure).
		fractal_data: Pointer to the t_fractol structure, containing data for cleanup.*/
	fractal_data->win = mlx_new_window(fractal_data->mlx, WIDTH, HEIGHT, "Fractol - 42 Project");
	/*It calls the mlx_new_window function to create a new window using the previously 
	initialized MLX instance (fractal_data->mlx). It sets the window width, height, 
	and title ("Fractol").
	The return value is stored in fractal_data->win.*/
	if (!fractal_data->win)
		clean_exit(msg("MLX: error creating window.", "", 1), fractal_data);
	fractal_data->sx = 2.0;
	/*This line sets the initial scaling factor for the viewing area (fractal_data->sx) to 2.0. 
	This value controls how much of the complex plane is displayed in the window.*/
	fractal_data->rx = 0.5;
	/*This line sets the initial escape radius for the Mandelbrot calculation 
	(fractal_data->rx) to 0.5. This parameter is used in determining 
	if a point belongs to the Mandelbrot set.*/
	fractal_data->fx = 1.0;
	/*This line sets the initial fold parameter for the Mandelbox calculation 
	(fractal_data->fx) to 1.0. This parameter is specific to the Mandelbox set.*/
	get_complex_layout(fractal_data);
	color_shift(fractal_data);
}
