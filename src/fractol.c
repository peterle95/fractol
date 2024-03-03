/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:41:55 by pmolzer           #+#    #+#             */
/*   Updated: 2024/02/21 01:41:55 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* type_comparison:
*	Parses the given fractal type argument and checks against
*	the name (i.e. "mandelbrot"), the associated letter (i.e. "M")
*	and the associated number (i.e. "1").
*	Returns true if the argument matches one of these requirements,
*	false if not.
*/
int	type_comparison(char *av, char *str, char c, char n)
{
	int	i;

	i = 0;
	while (av[i])
	{
		av[i] = ft_tolower(av[i]);
		i++;
	}
	if (!ft_strncmp(av, str, ft_strlen(str) + 1))
		return (1);
	else if (av[1] == '\0' && (av[0] == c || av[0] == n))
		return (1);
	return (0);
}

/* get_set:
*	Retrieves the set specified in program arguments.
*	If no valid set was provided, it displays a help
*	message and quits the program.
*/
void	get_set(t_fractol *fractal_data, char **av)
{
	if (type_comparison(av[1], "mandelbrot", 'm', '1'))
		fractal_data->set = MANDELBROT;
	else if (type_comparison(av[1], "julia", 'j', '2'))
		fractal_data->set = JULIA;
	else
		help_msg(fractal_data);
}

/* get_julia_starting_values:
*	Checks whether starting values were provided at program launch
*	for the Julia set. If not, default Julia values are assigned.
*	If values were provided, parses them, returning an error message
*	if the values are not valid.
*/
void	get_julia_starting_values(t_fractol *fractal_data, int ac, char **av)
{
	if (fractal_data->set != JULIA || ac == 2)
	{
		fractal_data->kr = -0.766667;
		fractal_data->ki = -0.090000;
		return ;
	}
	if (ac == 3)
		help_msg(fractal_data);
	if (!ft_strchr(av[2], '.'))
		help_msg(fractal_data);
	if (!ft_strchr(av[3], '.'))
		help_msg(fractal_data);
	f->kr = ft_atof(av[2]);
	f->ki = ft_atof(av[3]);
	if (fractal_data->kr > 2.0 || fractal_data->kr < -2.0)
		help_msg(f);
	if (fractal_data->ki >= 2.0 || fractal_data->ki <= -2.0) // can I delete one of the if statements? Wouldn't it be enough >= & <=?
		help_msg(f);
}

/* handle_args:
*	Retrieves the set, the julia starting values and the color from
*	the arguments passed at program launch.
*/
void	handle_args(t_fractol *fractal_data, int ac, char **av)
{
	get_set(fractal_data, av);
	if (fractal_data->set != JULIA && ac > 3)
		help_msg(fractal_data);
	else if (fractal_data->set == JULIA && ac > 5)
		help_msg(fractal_data);
	get_julia_starting_values(fractal_data, ac, av);
	get_color(fractal_data, ac, av);
}

/* main:
*	Initializes the fractol data structure, prints the program controls,
*	opens a new window and registers hooks to detect user interactions.
*	Loops infinitely until the user quits the process.
*/
int	main(int ac, char **av)
{
	t_fractol	fractal_data;

	/*The reason you need t_fractol f in main is 
	because almost all functions you call take the t_fractol structure
	 as an argument. This structure holds all the data needed for the
	  fractal calculation and rendering process. By passing f to these 
	  functions, you provide them with the necessary information to work 
	  with the chosen fractal type, colors, zoom level, and other 
	  settings.*/

	if (ac < 2)
		help_msg(&fractal_data);
	clean_init(&fractal_data); // Initializes the structure members to default values, ensuring a consistent starting state.
	handle_args(&fractal_data, ac, av);
	/*Reads command-line arguments and sets values in the f structure based on user input 
	(e.g., chosen fractal type, starting values).*/
	init(&fractal_data);
	/*Initializes graphics resources and libraries, potentially using 
	parameters from the fractal_dats structure.*/
	render(&fractal_data);
	/*Calculates and draws the fractal image, using data like 
	set, min_r, max_r, etc. stored in f*/
	print_controls();
	mlx_hook(fractal_data.win, EVENT_CLOSE_BTN, 0, end_fractol, &fractal_data);
	/*This line registers a hook for the window close button event.
	f.win is the pointer to the main window object created by MiniLibX.
	EVENT_CLOSE_BTN is a constant defined earlier in the code, likely 
	representing the specific code for the window close button event
	 within MiniLibX.
	0 is an optional parameter often used to specify specific data 
	about the event (not used here).
	end_fractol is the function pointer that will be called when the 
	window close button is clicked. This function likely performs 
	necessary cleanup tasks like deallocating memory and exiting 
	the program gracefully.
	&f passes the address of the t_fractol structure (f) to the 
	end_fractol function. This allows the function to access and 
	potentially modify data related to the fractal calculation and 
	rendering.*/
	mlx_key_hook(fractal_data.win, key_event, &fractal_data);
	/*This line registers a hook for keyboard events on the window.
Similar to the first line, it specifies the window object, event type 
(key_event), and passes the end_fractol function pointer with the f 
structure address.
The key_event function (not shown) will be called every time a key is 
pressed or released on the keyboard. It likely checks the pressed key 
and performs actions based on predefined key mappings to interact with 
the fractal, change settings, or trigger other functionalities.*/
	mlx_mouse_hook(fractal_data.win, mouse_event, &fractal_data);
	/*This line registers a hook for mouse events on the window.
It follows the same structure as the previous lines, using the 
mouse_event function (not shown) to handle various mouse interactions 
like clicks, scrolls, and dragging. These events can be used to zoom, 
pan, change colors, or implement other user interactions within the 
program.*/
	mlx_loop(fractal_data.mlx);
	/*This line initiates the main event loop of the MiniLibX library.
It starts listening for events like window close, key presses, mouse 
interactions, and others based on the registered hooks.
When an event occurs, the corresponding function (end_fractol, 
key_event, or mouse_event) will be called to handle it.
The loop continues indefinitely until an event triggers program 
termination or specific conditions are met.*/
}
