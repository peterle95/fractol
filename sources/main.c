/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:14:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/16 14:28:56 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	draw_fractal(t_data *data)
{
	if (data->fractal_type == MANDELBROT)
		draw_mandelbrot(data);
	else if (data->fractal_type == MANDELBROT2)
		draw_mandelbrot2(data);
	else if (data->fractal_type == MANDELBROT3)
		draw_mandelbrot3(data);
	else if (data->fractal_type == MANDELBROT4)
		draw_mandelbrot4(data);
	else if (data->fractal_type == JULIA)
		draw_julia(data);
	else if (data->fractal_type == JULIA2)
		draw_julia2(data);
	else if (data->fractal_type == JULIA3)
		draw_julia3(data);
	else if (data->fractal_type == JULIA4)
		draw_julia4(data);
	else
		printf("Error: Invalid fractal type\n");
}

int julia_checker(t_data *data, int argc, char **argv)
{
    data->fractal_type = JULIA;
    if (argc == 4)
    {
        if (validate_julia(argv[2]) || validate_julia(argv[3]))
                return (1);
        data->julia_ci = convert_float(argv[2]);
        data->julia_cr = convert_float(argv[3]);
        if (data->julia_ci == -42.0 || data->julia_cr == -42.0)
            return (1);
        if (data->julia_ci < -2.0 || data->julia_ci > 2.0 || 
            data->julia_cr < -2.0 || data->julia_cr > 2.0)
                    return (1);
                return (0);
    }
    else if (argc == 3 || argc > 4)
        return (1);
	else
		return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 2)
		return (0);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		if (argc > 2)
			return (0);
		else
			data->fractal_type = MANDELBROT;
	}
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		if (julia_checker(data, argc, argv) != 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_data(&data))
	{
		printf("Error: Failed to initialize\n");
		return (1);
	}
	if (!parse_args(argc, argv, &data))
	{
		print_usage();
		exit_program(&data);
		return (1);
	}
	draw_fractal(&data);
	mlx_hook(data.window, 17, 0, exit_program, &data);
	/*This function sets up an event hook for the window close button (event 17).
	When the user clicks the close button, it calls the exit_program function.
	This function sets up a specific event hook. 

	17 corresponds to the DestroyNotify event (window close button).
	0 is the mask (not used in this case).
	exit_program is the function to be called when this event occurs.
	&data is passed as a parameter to the exit_program function.*/
	mlx_key_hook(data.window, key_hook, &data);
	/*This sets up a hook for keyboard events.
	Whenever a key is pressed, the key_hook function is called.
	This is a simplified version of mlx_hook specifically for key release events.

	It sets up the key_hook function to be called when a key is released.
	Internally, it's equivalent to setting up a hook for the KeyRelease event with KeyReleaseMask.*/
	mlx_mouse_hook(data.window, mouse_event, &data);
	/*This sets up a hook for mouse events.
	When mouse buttons are clicked or scrolled, the mouse_event function is called.
	It sets up the mouse_event function to be called when a mouse button is pressed.
	Internally, it's equivalent to setting up a hook for the ButtonPress event with ButtonPressMask.*/
	mlx_loop(data.mlx_connect);
	/*This function starts the main event loop of the program.
	It keeps the window open and continuously checks for events (key presses, mouse clicks, etc.).
	The program will stay in this loop until the window is closed.
	It sets up the event mask for all windows.
	It enters a loop that continues as long as there are windows and end_loop is not set.
	In each iteration:
	
	If there are pending events, it processes them:
	
	It retrieves the next event with XNextEvent.
	It finds the window associated with the event.
	If it's a window close event, it calls the DestroyNotify hook if set.
	For other events, it calls the appropriate hook function based on the event type.
	
	If there are no pending events and a loop hook is set, it calls the loop hook function.
	
	The loop continues until all windows are closed or mlx_loop_end is called.*/
	return (0);
}

/*Event masks are a way to specify which types of events you're interested in receiving for a 
particular window or input device in X11-based systems (which MiniLibX is built on top of). 
They act as filters for events, allowing your application to listen for specific types of events while ignoring others.

In the context of X11 and MiniLibX:

1. Purpose:
   - Event masks help improve efficiency by reducing the number of events your application needs to process.
   - They allow you to selectively enable or disable certain types of events for specific windows.

2. Structure:
   - An event mask is typically a bitfield where each bit corresponds to a specific type of event.
   - Setting a bit to 1 means you want to receive that type of event, while 0 means you don't.

3. Common event mask bits:
   - KeyPressMask: For keyboard key press events
   - KeyReleaseMask: For keyboard key release events
   - ButtonPressMask: For mouse button press events
   - ButtonReleaseMask: For mouse button release events
   - PointerMotionMask: For mouse movement events
   - ExposureMask: For window exposure events (when a window needs to be redrawn)

4. Usage in MiniLibX:
   - In the provided code, you can see event masks being used in the `mlx_key_hook` and `mlx_mouse_hook` functions:
     ```c
     win->hooks[KeyRelease].mask = KeyReleaseMask;
     win->hooks[ButtonPress].mask = ButtonPressMask;
     ```
   - These set up the appropriate masks for key release and button press events respectively.

5. Combining masks:
   - You can combine multiple event masks using the bitwise OR operator (|) to listen for multiple types of events.

6. In `mlx_loop`:
   - The function `mlx_int_set_win_event_mask` is called, which likely sets up the combined event mask for all the hooks that have been set.

7. Efficiency:
   - By using event masks, the X server only sends the events your application has expressed interest in, 
   reducing unnecessary event processing and improving performance.

In summary, event masks in MiniLibX and X11 allow you to specify which types of events you want your 
application to receive, providing a way to filter and focus on relevant events for your program's 
functionality. This system helps in creating more efficient and responsive graphical applications.*/
