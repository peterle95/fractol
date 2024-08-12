/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:24 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/12 23:02:56 by pmolzer          ###   ########.fr       */
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

	/*^0^ DERIVATION OF MAX_IM:^0^
	This formula is crucial for maintaining the correct aspect ratio when displaying the fractal. Let's break it down step-by-step to understand its derivation and purpose.
	The formula:
		data->max_im = data->min_im + (data->max_re - data->min_re) * WIN_HEIGHT / WIN_WIDTH;
		
	Purpose:
	This formula calculates the maximum imaginary value (max_im) of the complex plane to be displayed, 
	ensuring that the aspect ratio of the complex plane matches the aspect ratio of the window.
	Derivation:
	
	Aspect Ratio Concept:
	
	Aspect ratio is the ratio of width to height.
	
	For the window: 		aspect_ratio_window = WIN_WIDTH / WIN_HEIGHT
	For the complex plane:  aspect_ratio_plane  = (max_re - min_re) / (max_im - min_im)
	
	
	Matching Aspect Ratios:
	
	To avoid distortion, we want these ratios to be equal:
	(max_re - min_re) / (max_im - min_im) = WIN_WIDTH / WIN_HEIGHT
	
	Solving for max_im:
	(max_im - min_im) = (max_re - min_re) * (WIN_HEIGHT / WIN_WIDTH)
	max_im = min_im + (max_re - min_re) * (WIN_HEIGHT / WIN_WIDTH)
	
	There are several reasons why we solve for max_im rather than other variables:

	Conventional Viewing Window:
	For many fractals, especially the Mandelbrot set, there's a conventional initial view that 
	captures the most interesting parts of the fractal.
	This view typically spans from -2 to 1 on the real axis, centering around -0.5.
	The imaginary axis is usually centered around 0, with min_im set to a negative value (often -1.5 or -1).
	
	
	Asymmetry of the Mandelbrot Set:
	The Mandelbrot set is not symmetrical about the real axis. It extends further in the positive imaginary direction than the negative.
	By fixing min_im and calculating max_im, we ensure we capture the full height of the set while maintaining aspect ratio.
	
	
	Simplicity and Consistency:
	By fixing three out of four boundaries (min_re, max_re, min_im) and calculating only one (max_im), 
	we maintain a consistent reference point for zooming and panning operations.
	
	
	Aspect Ratio Control:
	Solving for max_im allows us to easily adjust the vertical size of the viewing window to match the aspect ratio of the display window.
	This is particularly important because screen widths often vary more than heights across different devices.
	
	
	Intuitive Zooming:
	When zooming, it's often more intuitive to keep the bottom-left corner of the viewing window fixed 
	(defined by min_re and min_im) and adjust the top-right corner.*/
	data->zoom = 1.0;
	/*Sets the initial zoom level to 1.0 (no zoom).*/
	data->julia_ci = 0.15;
	data->julia_cr = -0.8;
}

int	init_data(t_data *data)
{
	data->mlx_connect = mlx_init();
	/*The function starts by initializing the MLX (MiniLibX) system using mlx_init(). 
	This function sets up the connection to the X server (the system that manages the display on Unix-like systems)
	 and returns a pointer to the MLX instance. The returned pointer is stored in data->mlx for future use.*/
	if (!data->mlx_connect)
		return (0);
	data->window = mlx_new_window(data->mlx_connect, WIN_WIDTH, WIN_HEIGHT, "Fract'ol");
	/*This creates a new window using the MLX library.
	WIN_WIDTH and WIN_HEIGHT are likely predefined constants for the window dimensions.
	"Fract'ol" is the title of the window.
	The window pointer is stored in data->win.*/
	init_fractal(data);
	return (1);
}
