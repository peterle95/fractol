/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:14:35 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/06 21:10:33 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

enum e_fractal_type
{
	MANDELBROT,
	MANDELBROT2,
	MANDELBROT3,
	MANDELBROT4,
	JULIA,
	JULIA2,
	JULIA3,
	JULIA4,
};

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		fractal_type;
	double	zoom;
	double	move_x;
	double	move_y;
	double	min_re;
	double	max_re;
	double	min_im;
	double	max_im;
	double	julia_ci;
	double	julia_cr;
}	t_data;

# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define MAX_ITERATIONS 500

// initialization
int		init_data(t_data *data);
void	init_fractal(t_data *data);

// rendering
void	draw_fractal(t_data *data);

// events
int		key_hook(int keycode, t_data *data);
int		mouse_event(int button, int x, int y, t_data *data);

// Utils
int		ft_strcmp(const char *s1, const char *s2);
double	convert_float(char *str);
void	print_usage(void);

// fractals
int		mandelbrot(double cr, double ci);
int		julia(double zr, double zi, double cr, double ci);
void	draw_mandelbrot(t_data *data);
void	draw_mandelbrot2(t_data *data);
void	draw_mandelbrot3(t_data *data);
void	draw_mandelbrot4(t_data *data);
void	draw_julia(t_data *data);
void	draw_julia2(t_data *data);
void	draw_julia3(t_data *data);
void	draw_julia4(t_data *data);

// exit program
int		exit_program(t_data *data);

// calculations
double	calculate_cr(t_data *data, int x);
double	calculate_ci(t_data *data, int y);
double	calculate_zr(t_data *data, int x);
double	calculate_zi(t_data *data, int y);

// pixels
void	pixel_mandelbrot(t_data *data, int x, int y);
void	pixel_mandelbrot2(t_data *data, int x, int y);
void	pixel_mandelbrot3(t_data *data, int x, int y);
void	pixel_mandelbrot4(t_data *data, int x, int y);
void	pixel_julia(t_data *data, int x, int y);
void	pixel_julia2(t_data *data, int x, int y);
void	pixel_julia3(t_data *data, int x, int y);
void	pixel_julia4(t_data *data, int x, int y);

// colors_julia
int		color_julia(t_data *data, double zr, double zi);
int		color_julia2(t_data *data, double zr, double zi);
int		color_julia3(t_data *data, double zr, double zi);
int		color_julia4(t_data *data, double zr, double zi);

// colors_madelbrot
int		color_mandelbrot(double cr, double ci);
int		color_mandelbrot2(double cr, double ci);
int		color_mandelbrot3(double cr, double ci);
int		color_mandelbrot4(double cr, double ci);

#endif
