/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:34:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/12 23:05:49 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	pixel_mandelbrot(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot(cr, ci);
	mlx_pixel_put(data->mlx_connect, data->window, x, y, color);
	/*The mlx_pixel_put function is a core part of the MinilibX library, which is used for creating 
	graphical applications in C, particularly in the context of the 42 school curriculum. Let's break 
	down this function and explain how it puts pixels on the window:
	mlx_pixel_put(data->mlx, data->win, x, y, color);
	
	data->mlx_connect: This is a pointer to the MLX connection structure. It represents the connection to the 
	X-server (on Linux) or to the relevant graphical system on other platforms. This connection is essential for any drawing operations.
	data->win: This is a pointer to the window structure. It represents the specific window where the pixel will be drawn.
	x and y: These are the coordinates where the pixel will be drawn. The origin (0,0) is typically at 
	the top-left corner of the window. x increases from left to right, and y increases from top to bottom.
	color: This is an integer representing the color of the pixel. It's usually in the format 0xRRGGBB, 
	where RR is red, GG is green, and BB is blue, each represented by two hexadecimal digits.
	
	When mlx_pixel_put is called, it performs several operations:
	
	It checks if the provided MLX connection and window pointers are valid.
	It verifies if the (x,y) coordinates are within the bounds of the window.
	It converts the color from the integer format to the format required by the underlying graphical system.
	It communicates with the X-server (or equivalent system) to request that a pixel be drawn at the specified location with the specified color.
	The X-server then updates the window's buffer with this new pixel information.
	Finally, the change is reflected on the screen when the window is refreshed.*/
}

/*Key points:

The Mandelbrot set is drawn by mapping each pixel to a point in the complex plane.
The color of each pixel is determined by how quickly the point escapes to 
	infinity under the Mandelbrot iteration, or if it stays bounded.
The actual Mandelbrot calculation and coloring logic are encapsulated in 
	the color_mandelbrot function.
This approach draws the fractal pixel by pixel, which can be slow for large windows. 
	For better performance, you might consider drawing to an image buffer and then displaying the entire image at once.*/
void	pixel_mandelbrot2(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	/*Calculates the real part of the complex number corresponding to the x-coordinate of the pixel.*/
	ci = calculate_ci(data, y);
	/*Calculates the imaginary part of the complex number corresponding to the y-coordinate of the pixel.*/
	color = color_mandelbrot2(cr, ci);
	/*Determines the color of the pixel based on how the point (cr, ci) behaves in the Mandelbrot set iteration*/
	mlx_pixel_put(data->mlx_connect, data->window, x, y, color);
	/*Draws the pixel with the calculated color at the (x, y) coordinate in the window.*/
}

/*int		mlx_pixel_put(t_xvar *xvar,t_win_list *win,
			      int x,int y,int color)
{
   XGCValues	xgcv;
   
   xgcv.foreground = mlx_int_get_good_color(xvar,color);
   XChangeGC(xvar->display,win->gc,GCForeground,&xgcv);
   XDrawPoint(xvar->display,win->window,win->gc,x,y);
   if (xvar->do_flush)
     XFlush(xvar->display);
}
This function is using the X11 library to draw pixels. Here's how it works:

- XGCValues xgcv;
Creates a structure to hold graphics context values.

- xgcv.foreground = mlx_int_get_good_color(xvar, color);
Converts the color value to a format that X11 can use.

- XChangeGC(xvar->display, win->gc, GCForeground, &xgcv);
Changes the graphics context to use the new foreground color.

- XDrawPoint(xvar->display, win->window, win->gc, x, y);
This is the actual function that draws the pixel.
It draws a single point at coordinates (x, y) in the specified window, using the current graphics context.


- if (xvar->do_flush) XFlush(xvar->display);
If flushing is enabled, it forces any pending requests to be sent to the X server.

Now, let's consider how this fits into the bigger picture of drawing the Mandelbrot set:
The draw_mandelbrot function loops through all pixels in the window.
For each pixel, pixel_mandelbrot is called, which:
Calculates the complex number corresponding to that pixel's position.
Determines the color based on the Mandelbrot set calculations.
Calls mlx_pixel_put to actually draw the pixel.

mlx_pixel_put then uses X11 functions to draw that single pixel with the calculated color.
This process repeats for every pixel in the window.
*/

void	pixel_mandelbrot3(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot3(cr, ci);
	mlx_pixel_put(data->mlx_connect, data->window, x, y, color);
}

void	pixel_mandelbrot4(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot4(cr, ci);
	mlx_pixel_put(data->mlx_connect, data->window, x, y, color);
}