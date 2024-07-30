/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:24 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/20 14:01:09 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*This function is responsible for setting up the initial state of the fractal viewer:

    - It defines the portion of the complex plane that will be displayed. 
	  The range from -2.0 to 1.0 on the real axis and -1.5 to 1.5 on the 
	  imaginary axis is a common initial view for the Mandelbrot set, 
	  as it captures the entire set.
	- The aspect ratio adjustment for max_im ensures that the fractal 
	  isn't distorted when displayed in the window.
	- The zoom level of 1.0 means no initial zoom.
	- The Julia set parameters are preset to create an interesting default 
	  Julia set. These can be changed to generate different Julia sets.*/
void	init_fractal(t_data *data)
{
	data->min_re = -2.0;
	data->max_re = 1.0;
	data->min_im = -1.5;
	data->max_im = data->min_im
		+ (data->max_re - data->min_re) * WIN_HEIGHT / WIN_WIDTH;
	/*Sets the initial viewing window for the fractal in the complex plane:

	min_re: Minimum real value (-2.0)
	max_re: Maximum real value (1.0)
	min_im: Minimum imaginary value (-1.5)
	max_im: Maximum imaginary value is calculated to maintain the aspect ratio of the window. 
		This ensures that the fractal isn't stretched.*/
	data->zoom = 1.0;
	/*Sets the initial zoom level to 1.0 (no zoom).*/
	data->julia_ci = 0.27;
	data->julia_cr = -0.7;
	/*Sets default Julia set parameters:
	julia_ci: Imaginary part of the Julia set constant (0.27)
	julia_cr: Real part of the Julia set constant (-0.7)*/
	// julia 0.27 -0.75
	//julia 0.15 -0.7
}

/*This function is crucial for setting up the graphical environment:

- It initializes the MLX system
- Creates a window
- Creates an image for drawing
- Sets up image properties
- Initializes fractal-specific data*/
int	init_data(t_data *data)
{
	data->mlx = mlx_init();
	/*The function starts by initializing the MLX (MiniLibX) system using mlx_init(). 
	This function sets up the connection to the X server and returns a pointer to the MLX instance.*/
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Fract'ol");
	/*Creates a new window using mlx_new_window(). It uses the MLX instance, 
	sets the window size (WIN_WIDTH and WIN_HEIGHT), and gives it the title "Fract'ol".*/
	if (!data->win)
	{
		free(data->mlx);
		return (0);
	}
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
	{
		mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
		return (0);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	/*Gets the memory address of the image using mlx_get_data_addr(). This function also provides information about the image format:

	bits_per_pixel: Number of bits used to represent a pixel color
	line_length: Number of bytes used to store one line of the image
	endian: Byte order (little or big endian)*/
	init_fractal(data);
	return (1);
}
