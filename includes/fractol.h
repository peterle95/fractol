/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:43:54 by pmolzer           #+#    #+#             */
/*   Updated: 2024/02/21 01:43:54 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include "keys.h"
# include <stdio.h>
# include <math.h>

/*  Dimensions	*/
# define WIDTH 900
# define HEIGHT 900
# define MAX_ITERATIONS 60

/*  Fractal sets	*/
# define MANDELBROT 1
# define JULIA 2

typedef struct t_fractol // changed from s_fractol
{
	void	*mlx;
	/*Purpose: This pointer holds a reference to an object or 
	data structure specific to the MiniLibX windowing system being used 
	(based on the presence of mlx.h). The actual data type stored here 
	would depend on MiniLibX's internal implementation.
	Function: It's used for drawing graphics and managing the window 
	where the fractal is displayed.*/
	void	*win;
	/*Purpose: Similar to mlx, this pointer holds a reference to a 
	window object created using MiniLibX functions.
	Function: It represents the specific window where the fractal 
	visualization is being drawn.*/
	void	*img;
	/*Purpose: This pointer holds a reference to an image object 
	created using MiniLibX functions. This image object serves as the 
	canvas where the fractal pixels are stored.
	Function: The program would manipulate this image data to render the 
	different colors and details of the fractal.*/
	char	*buf;
	/*Purpose: This is likely a pointer to a character buffer used for 
	storing temporary data or image information.
	Function: The exact purpose might depend on specific functions within 
	the program and how they handle image manipulation.*/
	int		set;
	/*Purpose: This integer variable stores the currently selected 
	fractal type.
	Function: The program might use constants like MANDELBROT or JULIA 
	(defined elsewhere) to represent different fractal sets, and this 
	variable would hold one of those values.*/
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	/*Purpose: These variables define the minimum and maximum values for 
	the real (r) and imaginary (i) components of the complex plane used to 
	calculate the fractal.
	Function: These values determine the viewing area of the complex 
	plane displayed in the fractal visualization.*/
	double	kr; 
	double	ki; 
	double	sx;
	/*Data type: double (double-precision floating-point number)
	Purpose:
	kr: This variable stores the real component of the complex number c 
	used in the Julia set calculation.
	ki: This variable stores the imaginary component of the complex number c 
	used in the Julia set calculation.
	sx: This variable might represent a scaling factor for the complex plane 
	view.
	Function:
	kr and ki are crucial for defining the specific Julia set being 
	visualized.
	sx might be used for zooming in or out on the complex plane.*/
	double	rx;
	double	fx;
	/*Purpose:
	rx: This variable's purpose is less clear without more context. 
	It might be another scaling factor or a rotation value for the complex 
	plane view.
	fx: This variable might represent an offset value for the complex plane 
	view, shifting the displayed area.
	Function: These variables potentially influence the specific region of 
	the complex plane that is visualized in the fractal.*/
	int		*palette;
	/*Purpose: This pointer likely points to an array of integers that 
	represent a color palette used for coloring the pixels in the fractal 
	visualization.
	Function: The program would use the values in this array to assign 
	different colors to different iteration counts based on the fractal 
	calculation.*/
	int		color_pattern;
	/*Purpose: This variable might store an integer value that defines the 
	type of color palette being used (e.g., monochrome, gradient, etc.).
	Function: In conjunction with the palette array, it determines the 
	color scheme applied to the fractal visualization.*/
	int		color;
	/*Purpose: The exact purpose of this variable depends on the overall 
	color management logic. It might hold a single color value used for 
	specific purposes.
	Function: Without*/
}	t_fractol;

/*  Fractal Sets   */
int		mandelbrot(double cr, double ci);
int		julia(t_fractol *fractal_data, double zr, double zi);

/*  Draw Fractal	*/
void	render(t_fractol *fractal_data);
void	set_pixel_color(t_fractol *fractal_data, int x, int y, int color);// ????? removed static
int	calculate_fractal(t_fractol *fractal_data, double pr, double pi); // ?????


/* Colors	*/
void	set_color_mono(t_fractol *fractal_data, int color);
void	set_color_multiple(t_fractol *fractal_data, int colors[4], int n);
void	set_color_zebra(t_fractol *fractal_data, int color);
void	set_color_triad(t_fractol *fractal_data, int color);
void	set_color_tetra(t_fractol *fractal_data, int color);
int		get_percent_color(int color, double percent);
int		interpolate(int startcolor, int endcolor, double fraction); // ??????
void	fill_color_stripe(t_fractol *fractal_data, int color, int stripe); // ??????


/*  Events   */
int		mouse_event(int keycode, int x, int y, t_fractol *mlx);
void	move(t_fractol *fractal_data, double distance, char direction); // ?????????
void	zoom(t_fractol *fractal_data, double zoom); // ??????



/* Initialization */
void	clean_init(t_fractol *fractal_data);
void	init_img(t_fractol *fractal_data);
void	reinit_img(t_fractol *fractal_data);
void	init(t_fractol *fractal_data);
void	get_complex_layout(t_fractol *fractal_data);

/*  Utils   */
int		end_fractol(t_fractol *mlx);
void	clean_exit(int error_code, t_fractol *fractal_data);
int		msg(char *str1, char *str2, int errno);

/*Parsing ???????*/

int	skip_space_sign_0x(char *color);
int	ft_atox_color(t_fractol *fractal_data, char *color);
void	get_color(t_fractol *fractal_data, int ac, char **av);
int	skip_space_sign(char *str, int *is_neg);
double	ft_atof(char *str);

/*Help message ???????*/

void	print_fractal_options(void);
void	print_color_options(void);
void	print_controls(void);
void	help_msg(t_fractol *fractal_data);


/*Main code ???????*/

int		type_comparison(char *av, char *str, char c, char n);
void	get_set(t_fractol *fractal_data, char **av);
void	get_julia_starting_values(t_fractol *fractal_data, int ac, char **av);
void	handle_args(t_fractol *fractal_data, int ac, char **av);


#endif
