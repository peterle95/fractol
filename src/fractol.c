/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:49:45 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/05 16:08:58 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* type_cmp:
*	Parses the given fractal type argument and checks against
*	the name (i.e. "mandelbrot"), the associated letter (i.e. "M")
*	and the associated number (i.e. "1").
*	Returns true if the argument matches one of these requirements,
*	false if not.
*/
static int	type_cmp(char *av, char *str, char c, char n)
{
	int	i;

	i = 0;
	while (av[i])
	{
		av[i] = ft_tolower(av[i]);
		/*converts the current character (av[i]) in the argument string to lowercase 
		using a function assumed to be called ft_tolower. This ensures case-insensitive 
		comparison (e.g., "Mandelbrot" and "mAnDeLbRoT" would both be considered matches).*/
		i++;
	}
	if (!ft_strncmp(av, str, ft_strlen(str) + 1))
	 	/*his function call (likely from an external library) compares the first 
		ft_strlen(str) (length of the reference name) characters of av and str. 
		The + 1 argument might be to include the null terminator in the comparison 
		for an exact match.*/
		return (1);
		/*If the comparison returns 0 (indicating a match), the function returns 1 (true) 
		directly, signifying a successful FULL NAME MATCH*/
	else if (av[1] == '\0' && (av[0] == c || av[0] == n))
		/*av[1] == '\0': 
		This condition ensures the argument string (av) has only one 
		character (length 1) after conversion to lowercase (ft_tolower).
		(av[0] == c || av[0] == n): 
		This condition checks if the single character in av matches either the short 
		name letter (c) or the associated number (n) of the reference fractal.*/
		return (1);
		/*If both conditions are met, the function returns 1 (true), indicating a 
		successful SINGLE CHARACTER MATCH*/
	return (0);
}

/* get_set:
*	Retrieves the set specified in program arguments.
*	If no valid set was provided, it displays a help
*	message and quits the program.
*/
static void	get_set(t_fractol *fractal_data, char **av)
{
	if (type_cmp(av[1], "mandelbrot", 'm', '1'))
		fractal_data->set = MANDELBROT;
	else if (type_cmp(av[1], "julia", 'j', '2'))
		fractal_data->set = JULIA;
	else if (type_cmp(av[1], "burning ship", 'b', '3'))
		fractal_data->set = BURNING_SHIP;
	else if (type_cmp(av[1], "tricorn", 't', '4'))
		fractal_data->set = TRICORN;
	else if (type_cmp(av[1], "mandelbox", 'x', '5'))
		fractal_data->set = MANDELBOX;
	else
		help_msg(fractal_data);
}

/* get_julia_starting_values:
*	Checks whether starting values were provided at program launch
*	for the Julia set. If not, default Julia values are assigned.
*	If values were provided, parses them, returning an error message
*	if the values are not valid.
*/
static void	get_julia_starting_values(t_fractol *fractal_data, int ac, char **av)
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
	fractal_data->kr = ft_atof(av[2]);
	fractal_data->ki = ft_atof(av[3]);
	if (fractal_data->kr > 2.0 || fractal_data->kr < -2.0)
		help_msg(fractal_data);
	if (fractal_data->ki >= 2.0 || fractal_data->ki <= -2.0)
		help_msg(fractal_data);
}

/* handle_args:
*	Retrieves the set, the julia starting values and the color from
*	the arguments passed at program launch.
	Extract information about the fractal type (set), 
	Julia set starting values (if applicable), and base color from the command-line arguments.
	Validate the number of arguments provided based on the chosen set type.

	WHY ONLY JULIA?
	The code checks for extra arguments specifically for the Julia set because it requires 
	two additional values (the real and imaginary parts) to define the starting point for 
	the Julia set calculation. The Mandelbrot set and potentially other fractal types might 
	not require any additional configuration beyond the set type itself (which defines the 
	calculation formula). Providing extra arguments for these sets would be unexpected and 
	might lead to errors, hence the validation.
*/
static void	handle_args(t_fractol *fractal_data, int ac, char **av)
{
	get_set(f, av);
	/*It parses the arguments (av) to determine the chosen fractal type (set) and 
	stores it in the fractal_data->set member of the structure.*/
	if (fractal_data->set != JULIA && ac > 3)
	/*This conditional statement checks if:
	The chosen set is not JULIA (i.e., Mandelbrot or another type).
	The number of arguments (ac) is greater than 3 (expecting only program name, set type, 
	and color).
	If both conditions are true, it calls a function named help_msg, 
	likely to display an error message or usage instructions because unexpected 
	arguments were provided for a non-Julia set.*/
		help_msg(fractal_data);
	else if (fractal_data->set == JULIA && ac > 5)
	/*This else-if statement checks if:
	The chosen set is JULIA.
	The number of arguments (ac) is greater than 5 
	(expecting program name, set type, Julia starting values (2 numbers), and color).
	If both conditions are true, it calls help_msg again, 
	likely indicating extra arguments were provided for the Julia set
	Only 5 arguemts are required for the JULIA set.*/
		help_msg(fractal_data);
	get_julia_starting_values(f, ac, av);
	/*This line calls a function named get_julia_starting_values that parses the arguments 
	(av) to extract the starting values for the Julia set calculation (if it was chosen) 
	and stores them in the appropriate members of the t_fractol structure 
	(possibly fractal_data->kr and fractal_data->ki).*/
	get_color(f, ac, av);
	/*This line calls a function named get_color that likely parses the arguments (av) 
	to extract the base color information and stores it in the fractal_data->color member 
		of the structure.*/
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
	clean_init(&fractal_data);
	/*Initializes the structure members to default values, 
	ensuring a consistent starting state.*/
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
	fractal_data.win is the pointer to the main window object created by MiniLibX.
	EVENT_CLOSE_BTN is a constant defined earlier in the code, likely 
	representing the specific code for the window close button event
	 within MiniLibX.
	0 is an optional parameter often used to specify specific data 
	about the event (not used here).
	end_fractol is the function pointer that will be called when the 
	window close button is clicked. This function likely performs 
	necessary cleanup tasks like deallocating memory and exiting 
	the program gracefully.
	&fractal_data passes the address of the t_fractol structure (fractal_data) to the 
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
	mlx_loop(f.mlx);
	/*This line initiates the main event loop of the MiniLibX library.
It starts listening for events like window close, key presses, mouse 
interactions, and others based on the registered hooks.
When an event occurs, the corresponding function (end_fractol, 
key_event, or mouse_event) will be called to handle it.
The loop continues indefinitely until an event triggers program 
termination or specific conditions are met.*/
}
