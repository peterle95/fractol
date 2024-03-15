#include<stdio.h>
#include<unistd.h>

int	main()
{
printf("\e[31m                   :::       ::::::::\n");
printf("\e[32m                  :+:      :+:     :+:\n");
printf("\e[33m                 +:+  +:+         +:+\n");
printf("\e[34m                +#+  +:+        +#+\n");
printf("\e[35m               +#+#+#+#+#+    +#+\n");
printf("\e[36m                   #+#     #+#\n");
printf("\e[31m                  ###    ########.fr\n");

sleep(3);
printf("\e[0m\n+====================================================+\n");
printf("|              FRACT'OL by pmolzer                   |\n");
printf("+====================================================+\n\n");

printf("\e[36m~~~~~~~~~~~~~~~~  Available Fractals  ~~~~~~~~~~~~~~~~\e[0m\n\n");
printf("Which fractal would you like to view?\n\n");
sleep(1.5);	
printf("\tM - Mandelbrot\n");
sleep(1.5);	
printf("\tJ - Julia\n");
// printf("\tB - Burning Ship\n");
// printf("\tT - Tricorn\n");
// printf("\tX - Mandelbox\n");
sleep(1.5);	
printf("Usage example:\t./fractol <type>\n\t\t./fractol M\n");
sleep(1.5);
printf("\nFor Julia, you may specify starting values for the\n");
sleep(1.5);
printf("initial fractal shape. Values must be between\n");
sleep(1.5);
printf("-2.0 and 2.0 and must contain a decimal point.\n");
sleep(1.5);
printf("Usage example:\t\n");
sleep(1.5);
printf("./fractol J\n\t\t./fractol J 0.285 0.01\n");

sleep(3);

printf("\e[36m\n~~~~~~~~~~~~~~~~~~  Color Display  ~~~~~~~~~~~~~~~~~~~\e[0m\n\n");
sleep(1.5);
printf("Pick a display color by providing a hexadecimal code.\n");
sleep(1.5);
printf("The hex color code must be formatted as RRGGBB:\n\n");
sleep(1.5);
printf("\tWhite:\tFFFFFF\t\tBlack:\t000000\n");
sleep(1.5);
printf("\tRed:\tFF0000\t\tGreen:\t00FF00\n");
sleep(1.5);
printf("\tBlue:\t0000FF\t\tYellow:\tFFFF00\n");
sleep(1.5);
printf("Other interesting colors:\n");
sleep(1.5);
printf("\tPurple:\t9933FF\t\tOrange:\tCC6600\n");
sleep(1.5);
printf("\tPink:\tFF3399\t\tTurquoise: 00FF80\t\n\n");
sleep(1.5);
printf("Usage example:\t\n");
sleep(1.5);
printf("./fractol <type> <color>\n");
sleep(1.5);
printf("\t\t./fractol M 0066FF\e\n");
sleep(1.5);
printf("\nFor Julia, you can only specify colors after\n");
sleep(1.5);
printf("the starting values.\n");
sleep(1.5);
printf("Usage example:\t\n");
sleep(1.5);
printf("./fractol J 0.285 0.01 CC6600\e\n");
sleep(1.5);



printf("\e[36m\n~~~~~~~~~~~~~~~~~~~~~  Controls  ~~~~~~~~~~~~~~~~~~~~~~\e[0m\n\n");
sleep(1.5);
printf("WASD or arrow keys\tmove view.\n");
sleep(1.5);
printf("+/- or scroll wheel\tzoom in and out.\n");
sleep(1.5);
printf("Spacebar\t\tchange color schemes.\n");
sleep(1.5);
printf("Left click\t\tshift Julia set [Julia only].\n");
sleep(1.5); // change this
printf("1, 2, 3, 4, 5\t\tswitch fractals.\n");
sleep(1.5); // change this
printf("ESC or close window\tquit fract'ol.\n\n");
sleep(1.5);
printf("+====================================================+\n\n");
} 



// ORIGINAL:

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:49:38 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/07 22:13:08 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "fractol.h"

/* print_fractal_options:
	Prints an explanation of the fractal options that can be specified
	at program launch.
*/
/* void	print_fractal_options(void)
{
	ft_putendl_fd("+===============  Available Fractals  ===============+", 1);
	ft_putendl_fd("Which fractal would you like to view?", 1);
	sleep(2);
	ft_putendl_fd("\tM - Mandelbrot", 1);
	sleep(2);
	ft_putendl_fd("\tJ - Julia", 1);
	// ft_putendl_fd("\tB - Burning Ship", 1);
	// ft_putendl_fd("\tT - Tricorn", 1);
	// ft_putendl_fd("\tX - Mandelbox", 1);
	sleep(2);
	ft_putendl_fd("\e[36mUsage example:\t./fractol <type>\n\t\t./fractol M\e[0m", 1);
	ft_putstr_fd("\nFor Julia, you may specify starting values for the\n", 1);
	ft_putstr_fd("initial fractal shape. Values must be between\n", 1);
	ft_putendl_fd("-2.0 and 2.0 and must contain a decimal point.", 1);
	ft_putendl_fd("\e[36mUsage example:\t", 1);
	ft_putendl_fd("./fractol J\n\t\t./fractol J 0.285 0.01\e[0m", 1);
} */

/* print_color_options:
	Prints an explanation of the color options that can be specified
	at program launch.
*/
/* void	print_color_options(void)
{
	ft_putendl_fd("\n+===============  Color Display  ====================+", 1);
	ft_putendl_fd("Pick a display color by providing a hexadecimal code.", 1);
	ft_putendl_fd("The hex color code must be formatted as RRGGBB:", 1);
	ft_putendl_fd("\tWhite:\tFFFFFF\t\tBlack:\t000000", 1);
	ft_putendl_fd("\tRed:\tFF0000\t\tGreen:\t00FF00", 1);
	ft_putendl_fd("\tBlue:\t0000FF\t\tYellow:\tFFFF00", 1);
	ft_putendl_fd("Other interesting colors:", 1);
	ft_putendl_fd("\tPurple:\t9933FF\t\tOrange:\tCC6600", 1);
	ft_putendl_fd("\tPink:\tFF3399\t\tTurquoise: 00FF80\t", 1);
	ft_putstr_fd("\e[36mUsage example:\t", 1);
	ft_putendl_fd("./fractol <type> <color>", 1);
	ft_putendl_fd("\t\t./fractol M 0066FF\e[0m", 1);
	ft_putendl_fd("\nFor Julia, you can only specify colors after", 1);
	ft_putendl_fd("the starting values.", 1);
	ft_putstr_fd("\e[36mUsage example:\t", 1);
	ft_putendl_fd("./fractol J 0.285 0.01 CC6600\e[0m", 1);
} */

/* print_controls:
	Prints a list of program controls to the standard output when the program
	launches successfully.
*/
/* void	print_controls(void)
{
	ft_putendl_fd("\n+===============  Controls  =========================+", 1);
	ft_putendl_fd("WASD or arrow keys\tmove view.", 1);
	ft_putendl_fd("+/- or scroll wheel\tzoom in and out.", 1);
	ft_putendl_fd("Spacebar\t\tchange color schemes.", 1);
	ft_putendl_fd("Left click\t\tshift Julia set [Julia only].", 1); // change this
	ft_putendl_fd("1, 2, 3, 4, 5\t\tswitch fractals.", 1); // change this
	ft_putendl_fd("ESC or close window\tquit fract'ol.", 1);
	ft_putendl_fd("+====================================================+\n", 1);
} */

/* help_msg:
	Prints a help message to the standard output to explain the program options.
*/
/* void	help_msg(t_fractol *fractal_data)
{
	ft_putendl_fd("\n+====================================================+", 1);
	ft_putendl_fd("|                     FRACT'OL                       |", 1);
	ft_putendl_fd("+====================================================+\n", 1);
	print_fractal_options();
	print_color_options();
	clean_exit(EXIT_FAILURE, f);
}  */
