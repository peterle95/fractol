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
	void	*win;
	void	*img;
	char	*buf;
	int		set;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	double	kr; // real numbers
	double	ki; // imaginary numbers
	double	sx;
	double	rx;
	double	fx;
	int		*palette;
	int		color_pattern;
	int		color;
}	t_fractol;

/*  Fractal Sets   */
int		mandelbrot(double cr, double ci);
int		julia(t_fractol *fractal_data, double zr, double zi);

/*  Draw Fractal	*/
void	render(t_fractol *fractal_data);
static void	set_pixel_color(t_fractol *fractal_data, int x, int y, int color);// ?????
static int	calculate_fractal(t_fractol *fractal_data, double pr, double pi); // ?????


/* Colors	*/
void	set_color_mono(t_fractol *fractal_data, int color);
void	set_color_multiple(t_fractol *fractal_data, int colors[4], int n);
void	set_color_zebra(t_fractol *fractal_data, int color);
void	set_color_triad(t_fractol *fractal_data, int color);
void	set_color_tetra(t_fractol *fractal_data, int color);
int		get_percent_color(int color, double percent);
static int	interpolate(int startcolor, int endcolor, double fraction); // ??????
static void	fill_color_stripe(t_fractol *fractal_data, int color, int stripe); // ??????


/*  Events   */
int		mouse_event(int keycode, int x, int y, t_fractol *mlx);
static void	move(t_fractol *fractal_data, double distance, char direction); // ?????????
static void	zoom(t_fractol *fractal_data, double zoom); // ??????



/* Initialization */
void	clean_init(t_fractol *fractal_data);
static void	init_img(t_fractol *fractal_data);
void	reinit_img(t_fractol *fractal_data);
void	init(t_fractol *fractal_data);
void	get_complex_layout(t_fractol *fractal_data);

/*  Utils   */
int		end_fractol(t_fractol *mlx);
void	clean_exit(int error_code, t_fractol *fractal_data);
int		msg(char *str1, char *str2, int errno);
void	help_msg(t_fractol *fractal_data);
void	print_controls(void);

/*Parsing ???????*/

static int	skip_space_sign_0x(char *color);
static int	ft_atox_color(t_fractol *fractal_data, char *color);
void	get_color(t_fractol *fractal_data, int ac, char **av);
static int	skip_space_sign(char *str, int *is_neg);
double	ft_atof(char *str);

/*Help message ???????*/

void	print_fractal_options(void);
void	print_color_options(void);
void	print_controls(void);
void	help_msg(t_fractol *fractal_data);


/*Main code ???????*/

static int	type_cmp(char *av, char *str, char c, char n);
static void	get_set(t_fractol *fractal_data, char **av);
static void	get_julia_starting_values(t_fractol *fractal_data, int ac, char **av);
static void	handle_args(t_fractol *fractal_data, int ac, char **av);


#endif
