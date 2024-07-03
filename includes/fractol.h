/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:14:35 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/03 14:30:51 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include "../libft/libft.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


enum e_fractal_type {
  MANDELBROT,
  JULIA,  
};

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
    int     fractal_type;
    double  zoom;
    double  move_x;
    double  move_y;
    double  julia_x;
    double  julia_y;
    double  min_re;
    double  max_re;
    double  min_im;
    double  max_im;
    double julia_ci;
    double julia_cr;
    enum    e_fractal_type fractal;
    // Add any other necessary variables
} t_data;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MAX_ITERATIONS 500

// main
int     main(int argc, char **argv);

// initialization
int    init_data(t_data *data);
void    init_fractal(t_data *data);


// rendering
int     render(t_data *data);
void    draw_fractal(t_data *data);

// events
int     key_hook(int keycode, t_data *data);
int     mouse_hook(int button, int x, int y, t_data *data);

// Utils
int	ft_strcmp(const char *s1, const char *s2);
double    ft_atof(char *str);

// fractals
int mandelbrot(double cr, double ci, int max_iterations);
void draw_mandelbrot(t_data *data);
void draw_julia(t_data *data);

// exit program
int close_window(t_data *data);



#endif