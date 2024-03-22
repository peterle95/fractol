/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:49:51 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/22 16:34:47 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* zoom:
	Zooms the view of the fractal in or out by adjusting
	the complex number edge values by a zoom multiplier.
	The fractal can then be generated again at a different resolution,
	giving the appearance of zooming in or out.
	If the zoom multiplier is small, like 0.5, the view will
	zoom in, if it is big, like 2.0, it will zoom out.
*/
static void	zoom(t_fractol *fractal_data, double zoom)
{
	double	center_r;
	double	center_i;

	center_r = fractal_data->min_r - fractal_data->max_r;
	/* This line calculates the width of the current view in the real number plane 
	by subtracting the minimum real value (fractal_data->min_r) from the maximum (fractal_data->max_r).*/
	center_i = fractal_data->max_i - fractal_data->min_i;
	/*This line calculates the height of the current view in the imaginary 
	number plane using the same logic as for the real component.*/
	
	/*The next four lines adjust the minimum and maximum real/imaginary values 
	(fractal_data->min_r, fractal_data->max_r, fractal_data->min_i, fractal_data->max_i) 
	to achieve zooming:*/
	fractal_data->max_r = fractal_data->max_r + (center_r - zoom * center_r) / 2;
	/*This calculates the amount to adjust the center point based on the zoom factor (zoom)
	A smaller zoom value (like 0.5) represents zooming in. Multiplying the center width (center_r) 
	by zoom results in a smaller value to be subtracted from the center. 
	Dividing by 2 ensures the center point remains centered after adjustment.
	A larger zoom value (like 2.0) represents zooming out. 
	Multiplying by zoom results in a larger value to be added to the center, 
	effectively moving it away from the current view.*/
	fractal_data->min_r = fractal_data->max_r + zoom * center_r;
	/*This line adjusts the maximum real value by adding/subtracting half 
	the calculated adjustment amount from the current center point (fractal_data->max_r).*/
	fractal_data->min_i = fractal_data->min_i + (center_i - zoom * center_i) / 2;
	/*This line calculates the new minimum real value based on the adjusted 
	maximum (fractal_data->max_r) and the entire center width (zoom * center_r). 
	This ensures the view maintains its width after the zoom operation.*/
	fractal_data->max_i = fractal_data->min_i + zoom * center_i;
	/*The calculations for the imaginary component 
	(fractal_data->min_i and fractal_data->max_i) follow the same logic as the real component, 
	adjusting the view height in the imaginary number plane.*/
}

/* move:
	Moves the view of the fractal by adjusting the complex
	number edge values a certain distance in a certain direction.
*/
static void	move(t_fractol *fractal_data, double distance, char direction)
{
	double	center_r;
	double	center_i;

	center_r = fractal_data->max_r - fractal_data->min_r;
	center_i = fractal_data->max_i - fractal_data->min_i;
	/*These lines calculate the width of the currently displayed complex 
	plane in both the real and imaginary directions. 
	This effectively represents the "center" of the view.*/
	if (direction == 'R')
	{
		fractal_data->min_r += center_r * distance;
		fractal_data->max_r += center_r * distance;
		/*These lines add the calculated center_r (width) multiplied by the distance to both min_r and max_r. 
		This effectively shifts the entire displayed complex plane to the right by the specified distance.*/
	}
	else if (direction == 'L')
	{
		fractal_data->min_r -= center_r * distance;
		fractal_data->max_r -= center_r * distance;
		/*Represents moving to the left (similar logic as 'R' but subtracting center_r)*/
	}
	else if (direction == 'D')
	{
		fractal_data->min_i -= center_i * distance;
		fractal_data->max_i -= center_i * distance;
		/*Represents moving down (similar logic as 'R' but subtracting center_i for the imaginary component).*/
	}
	else if (direction == 'U')
	{
		fractal_data->min_i += center_i * distance;
		fractal_data->max_i += center_i * distance;
		/*Represents moving up (similar logic as 'R' but adding center_i)*/
	}
}

/* key_event_extend:
	Handles events from the keyboard keys:
		- 1, 2, 3, 4, 5: switch fractals
	This function is registered to an MLX hook and will
	automatically be called when the user does anything inside the
	program window with the keyboard.
	If a valid event is detected, settings are adjusted and the fractal
	gets redrawn.
*/
static int	key_event_extend(int keycode, t_fractol *mlx)
{
	/*keycode: The integer code representing the pressed key.
	mlx: Pointer to the t_fractol structure containing fractal data and settings.*/
	if (keycode == KEY_ONE && mlx->set != MANDELBROT)
		mlx->set = MANDELBROT;
	else if (keycode == KEY_TWO && mlx->set != JULIA)
		mlx->set = JULIA;
	else if (keycode == KEY_THREE && mlx->set != BURNING_SHIP)
		mlx->set = BURNING_SHIP;
	else if (keycode == KEY_FOUR && mlx->set != TRICORN)
		mlx->set = TRICORN;
	else if (keycode == KEY_FIVE && mlx->set != MANDELBOX)
		mlx->set = MANDELBOX;
	else
		return (1);
	get_complex_layout(mlx);
	/*After potentially changing the fractal type, the function calls:
		get_complex_layout(mlx): This function recalculates the complex number planes based 
		on the new fractal type. This is necessary because different fractals use different 
		mathematical formulas that require adjustments to the complex plane representation.*/
	render(mlx);
	/*render(mlx): This function is responsible for redrawing the fractal on the screen. 
	Since the type or complex plane layout might have changed, a redraw is necessary.*/
	return (0);
}

/* key_event:
	Handles events from the keyboard keys:
		- + or - key: zoom
		- Arrow keys or WASD: move
		- Space: color shift
	This function is registered to an MLX hook and will
	automatically be called when the user does anything inside the
	program window with the keyboard.
	If a valid event is detected, settings are adjusted and the fractal
	gets redrawn.
*/
int	key_event(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_ESC)
	{
		end_fractol(mlx);
		return (0);
	}
	else if (keycode == KEY_PLUS)
		zoom(mlx, 0.5);
	else if (keycode == KEY_MINUS)
		zoom(mlx, 2);
	else if (keycode == KEY_UP || keycode == KEY_W)
		move(mlx, 0.2, 'U');
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move(mlx, 0.2, 'D');
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		move(mlx, 0.2, 'L');
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		move(mlx, 0.2, 'R');
	else if (keycode == KEY_SPACE)
		color_shift(mlx);
	else if (!key_event_extend(keycode, mlx))
	/*If none of the above conditions match and the key_event_extend function 
	returns 0 (indicating it handled the event):
	This means the extended key handler likely processed a key between 1 and 5 to switch 
	between different fractal types (Mandelbrot, Julia, etc.).
	The function returns 1, indicating that the event has been consumed by the extended handler.
	Otherwise, it returns 1, indicating that the event wasn't handled by any of the conditions.*/
		return (1);
	else
		return (1);
	render(mlx);
	/*In all cases where the view or color scheme might have been modified (except KEY_ESC), 
	the function calls the render function (presumably responsible for redrawing the fractal on the screen)
	to reflect the changes.*/
	return (0);
}

/* mouse_event:
	Handles events from the mouse:
		- Mouse wheel: zoom
		- Left click: Julia shift
	This function is registered to an MLX hook and will
	automatically be called when the user does anything inside the
	program window with the mouse.
	If a valid event is detected, settings are adjusted and the fractal
	gets redrawn.
*/
int	mouse_event(int keycode, int x, int y, t_fractol *mlx)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(mlx, 0.5); // Calls zoom(mlx, 0.5) to zoom in the fractal by a factor of 0.5.
		x -= WIDTH / 2;
		y -= HEIGHT / 2;
		/*Calculates the relative mouse position by subtracting the 
		window's center coordinates (WIDTH / 2 and HEIGHT / 2):
			x represents the horizontal offset from the center.
			y represents the vertical offset from the center.
			This relative position helps maintain the clicked point as the center during zoom.*/
		if (x < 0)
		/*Checks if x is negative (mouse click was to the left of the center).*/
			move(mlx, (double)x * -1 / WIDTH, 'L');
			/*The calculation (double)x * -1 / WIDTH converts 
			the pixel offset (x) to a proportional value based 
			on the window width (WIDTH). The negative sign ensures a leftward movement.
			The 'L' character specifies a leftward movement for the move function.*/
		else if (x > 0)
			move(mlx, (double)x / WIDTH, 'R');
			/*Similarly, checks if x is positive 
			(mouse click was to the right of the center) and 
			calls move with a rightward movement ('R').*/
		if (y < 0)
			move(mlx, (double)y * -1 / HEIGHT, 'U');
		else if (y > 0)
			move (mlx, (double)y / HEIGHT, 'D');
		/*Similar logic is applied for the y coordinate.
			Checks if y is negative (mouse click was above the center) 
			and calls move with an upward movement ('U').
			Checks if y is positive (mouse click was below the center) 
			and calls move with a downward movement ('D').*/
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom(mlx, 2);
		/*If keycode is MOUSE_WHEEL_DOWN, calls zoom(mlx, 2) to zoom 
		out the fractal by a factor of 2.*/		
	else if (keycode == MOUSE_BTN)
	{
		if (mlx->set == JULIA)
			julia_shift(x, y, mlx);
			/*Checks if keycode is MOUSE_BTN (left click) and mlx->set is JULIA (indicating the Julia fractal is selected).
			If both conditions are met, it calls julia_shift(x, y, mlx). 
			This function adjusts parameters specific 
			to the Julia fractal based on the click position (x and y).*/
	}
	else
		return (0);
	render(mlx);
	return (0);
}
