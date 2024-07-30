/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:34:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/22 16:32:08 by pmolzer          ###   ########.fr       */
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
	mlx_pixel_put(data->mlx, data->win, x, y, color);
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
	mlx_pixel_put(data->mlx, data->win, x, y, color);
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
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_mandelbrot4(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot4(cr, ci);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}