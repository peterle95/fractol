/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:42:07 by pmolzer           #+#    #+#             */
/*   Updated: 2024/02/21 01:42:07 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* print_fractal_options:
*	Prints an explanation of the fractal options that can be specified
*	at program launch.
*/
void	print_fractal_options(void)
{
	ft_printf("~~~~~  Available Fractals  ~~~~~");
	ft_printf("Which fractal would you like to view?");
	sleep(1);
	ft_printf("\tM - Mandelbrot");
	sleep(1);
	ft_printf("\tJ - Julia");
	ft_printf("\e[36mUsage example:\t");
	ft_printf("./fractol <fractal_set>\n\t\t./fractol M\e[0m")
	ft_printf("\nFor Julia, you may specify starting values for the\n");
	ft_printf("initial fractal shape. Values must be between\n");
	ft_printf("-2.0 and 2.0 and must contain a decimal point.");
	ft_printf("\e[36mUsage example:\t");
	ft_printf("./fractol J\n\t\t./fractol J 0.285 0.01\e[0m");
}

/* print_color_options:
*	Prints an explanation of the color options that can be specified
*	at program launch.
*/
void	print_color_options(void)
{
	ft_printf("\n~~~~~ Color Display ~~~~~");
	ft_printf("Pick a display color by providing a hexadecimal code.");
	ft_printf("The hex color code must be formatted as RRGGBB:");
	ft_printf("\tWhite:\tFFFFFF\t\tBlack:\t000000");
	ft_printf("\tRed:\tFF0000\t\tGreen:\t00FF00");
	ft_printf("\tBlue:\t0000FF\t\tYellow:\tFFFF00");
	ft_printf("Other interesting colors:");
	ft_printf("\tPurple:\t9933FF\t\tOrange:\tCC6600");
	ft_printf("\tPink:\tFF3399\t\tTurquoise: 00FF80\t");
	ft_printf("\e[36mUsage example:\t");
	ft_printf("./fractol <fractal_set> <color>");
	ft_printf("\t\t./fractol M 0066FF\e[0m");
	ft_printf("\nFor Julia, you can only specify colors after");
	ft_printf("the starting values.");
	ft_printf("\e[36mUsage example:\t");
	ft_printf("./fractol J 0.285 0.01 CC6600\e[0m");
}

/* print_controls:
*	Prints a list of program controls to the standard output when the program
*	launches successfully.
*/
void	print_controls(void)
{
	ft_printf("\n~~~~~  Controls  ~~~~~");
	ft_printf("scroll wheel\tzoom in and out.");
	ft_printf("1, 2\t\t to switch fractals.");
	ft_printf("ESC or close window\tquit fract'ol.");
	ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/* help_msg:
*	Prints a help message to the standard output to explain the program options.
*/
void	help_msg(t_fractol *f)
{
	print_fractal_options();
	print_color_options();
	clean_exit(EXIT_FAILURE, f);
}
