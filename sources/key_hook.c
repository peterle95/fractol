
#include "../includes/fractol.h"

void	key_pressed(t_data *data, int keycode, double *move_x, double *move_y)
{
	if (keycode == 65307) // ESC key
		exit_program(data);
	else if (keycode == 65361) // Key Left
		*move_x = -0.1;
	else if (keycode == 65363) // Key Right
		*move_x = 0.1;
	else if (keycode == 65362) // Key UP
		*move_y = -0.1;
	else if (keycode == 65364) // Key Down
		*move_y = 0.1;
}

void	apply_movement(t_data *data, double move_x, double move_y)
{
	double	range_re;
	double	range_im;

	range_re = data->max_re - data->min_re;
	range_im = data->max_im - data->min_im;
	data->min_re += move_x * range_re;
	data->max_re += move_x * range_re;
	data->min_im += move_y * range_im;
	data->max_im += move_y * range_im;
	draw_fractal(data);
	/*This function, `apply_movement`, is responsible for shifting the viewing window of the fractal 
	based on user input. Let's break it down and then go through an example.

	1. Function purpose:
	   This function moves the viewing window of the fractal in the complex plane.

	2. Parameters:
	   - `data`: A pointer to the structure containing fractal viewing information.
	   - `move_x`: How much to move horizontally (as a fraction of the current view width).
	   - `move_y`: How much to move vertically (as a fraction of the current view height).

	3. Function steps:
	   a. Calculate the current range (width and height) of the viewing window.
	   b. Adjust the minimum and maximum values for both real and imaginary axes.
	   c. Redraw the fractal with the new viewing window.

	Now, let's go through an example:

	Suppose we have these initial values:
	```
	data->min_re = -2.0
	data->max_re = 1.0
	data->min_im = -1.5
	data->max_im = 1.5
	move_x = 0.1  (move right by 10% of the width)
	move_y = -0.05 (move up by 5% of the height)
	```

	Step-by-step calculation:

	1. Calculate ranges:
	   ```
	   range_re = 1.0 - (-2.0) = 3.0
	   range_im = 1.5 - (-1.5) = 3.0
	   ```

	2. Adjust real axis (x-direction):
	   ```
	   data->min_re += 0.1 * 3.0 = -2.0 + 0.3 = -1.7
	   data->max_re += 0.1 * 3.0 = 1.0 + 0.3 = 1.3
	   ```

	3. Adjust imaginary axis (y-direction):
	   ```
	   data->min_im += -0.05 * 3.0 = -1.5 + (-0.15) = -1.65
	   data->max_im += -0.05 * 3.0 = 1.5 + (-0.15) = 1.35
	   ```

	After this function, the new viewing window will be:
	```
	Real axis: [-1.7, 1.3]
	Imaginary axis: [-1.65, 1.35]
	```

	The viewing window has moved slightly to the right and up, maintaining its overall size but shifting its position in the complex plane.

	Key points:
	1. The movement is proportional to the current view size, allowing for consistent movement regardless of zoom level.
	2. Both min and max values are adjusted to maintain the window size.
	3. Negative `move_y` moves up because the imaginary axis typically increases upwards in mathematical graphs.

	After adjusting the viewing window, `draw_fractal(data)` is called to redraw the fractal
	 with these new boundaries, effectively creating the illusion of movement across the fractal.

	This approach allows for smooth navigation of the fractal, enabling users to explore 
	different areas of the complex plane where the fractal is defined.*/
}

int	key_hook(int keycode, t_data *data)
{
	double	move_x;
	double	move_y;
	int		fractal_changed;

	move_x = 0;
	move_y = 0;
	fractal_changed = 0;
	if (keycode == 65307 || (keycode >= 65361 && keycode <= 65364))
	/*This checks for the ESC key (65307) or arrow keys (65361-65364). If pressed, it calls key_pressed to handle movement or exit.*/
		key_pressed(data, keycode, &move_x, &move_y);
	else if (keycode >= 49 && keycode <= 56) // Keys between 1-8
	{
		data->fractal_type = keycode - 49;
		fractal_changed = 1;
	}
	else
		return (0);
	if (move_x != 0 || move_y != 0)
		apply_movement(data, move_x, move_y);
	if (fractal_changed != 0)
		draw_fractal(data);
	return (0);
}
