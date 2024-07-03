/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:14:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/03 18:35:18 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

#include <string.h>

int mouse_event(int button, int x, int y, t_data *data)
{
    double zoom_factor = 1.1;
    double center_re, center_im;
    (void)x;  // Unused parameter
    (void)y;  // Unused parameter

    // Calculate the center of the current view
    center_re = (data->min_re + data->max_re) / 2.0;
    center_im = (data->min_im + data->max_im) / 2.0;

    if (button == 4) // Scroll up to zoom in
    {
        data->zoom *= zoom_factor;
        data->min_re = center_re - (center_re - data->min_re) / zoom_factor;
        data->max_re = center_re + (data->max_re - center_re) / zoom_factor;
        data->min_im = center_im - (center_im - data->min_im) / zoom_factor;
        data->max_im = center_im + (data->max_im - center_im) / zoom_factor;
    }
    else if (button == 5) // Scroll down to zoom out
    {
        data->zoom /= zoom_factor;
        data->min_re = center_re - (center_re - data->min_re) * zoom_factor;
        data->max_re = center_re + (data->max_re - center_re) * zoom_factor;
        data->min_im = center_im - (center_im - data->min_im) * zoom_factor;
        data->max_im = center_im + (data->max_im - center_im) * zoom_factor;
    }

    // Redraw the fractal after zooming
    draw_fractal(data);

    return (0);
}

void draw_fractal(t_data *data)
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
    // Add more fractal types here if needed
}

// think about assigning 0.1 to MOVE_STEP. And the keys as well
int key_hook(int keycode, t_data *data)
{
    double move_x = 0;
    double move_y = 0;

    if (keycode == 65307) // ESC key
        close_window(data);
    else if (keycode == 65361) // Key Left
        move_x = -0.1;
    else if (keycode == 65363) // Key Right
        move_x = 0.1;
    else if (keycode == 65362) // Key UP
        move_y = -0.1;
    else if (keycode == 65364) // Key Down
        move_y = 0.1;
    else if (keycode == 49) // '1' key
        data->fractal_type = MANDELBROT;
    else if (keycode == 50) // '2' key
        data->fractal_type = MANDELBROT2;
    else if (keycode == 51) // '3' key
        data->fractal_type = MANDELBROT3;
    else if (keycode == 52) // '4' key
        data->fractal_type = MANDELBROT4;
    else if (keycode == 53) // '5' key
        data->fractal_type = JULIA;
    else if (keycode == 54) // '6' key
        data->fractal_type = JULIA2;
    else if (keycode == 55) // '7' key
        data->fractal_type = JULIA3;
    else if (keycode == 56) // '8' key
        data->fractal_type = JULIA4;  
    else
        return (0);

    // Apply movement
    if (move_x != 0 || move_y != 0)
    {
        double range_re = data->max_re - data->min_re;
        double range_im = data->max_im - data->min_im;
        data->min_re += move_x * range_re;
        data->max_re += move_x * range_re;
        data->min_im += move_y * range_im;
        data->max_im += move_y * range_im;
    }

    draw_fractal(data);
    return (0);
}


/*We create a separate parse_args function to handle the argument parsing. This keeps the main function clean and makes the code more modular.
We check if there's at least one argument (the program name is argc[0], so we need argc >= 2).
We use strcmp to check if the first argument is "mandelbrot" or "julia". This is simple and straightforward.
For the Mandelbrot set, we don't need additional parameters, so we just set the fractal type.
We check if exactly 3 arguments are provided (program name, "julia", and two parameters).
We validate each parameter using is_valid_float.
We convert the parameters to doubles using atof.
We check if the parameters are within the range -2 to 2, which is a common range for interesting Julia sets.

We return 0 from parse_args if:

The fractal type is not recognized.
The Julia set is selected but the number of arguments is incorrect.
The Julia set parameters are not valid floats.
The Julia set parameters are out of the acceptable range.*/
int parse_args(int argc, char **argv, t_data *data)
{
    if (argc < 2)
        return (0);
    
    if (ft_strcmp(argv[1], "mandelbrot") == 0)
    {
        data->fractal_type = MANDELBROT;
    }
    else if (ft_strcmp(argv[1], "julia") == 0)
    {
        data->fractal_type = JULIA;
        if (argc == 4)
        {
            data->julia_ci = convert_float(argv[2]);
            data->julia_cr = convert_float(argv[3]);
            if (data->julia_ci == -42.0 || data->julia_cr == -42.0 ||
                data->julia_ci < -2.0 || data->julia_ci > 2.0 ||
                data->julia_cr < -2.0 || data->julia_cr > 2.0)
                return (0);
        }
        else if (argc != 2)
            return (0);
    }
    else
        return (0);
    
    return (1);
}

int main(int argc, char **argv)
{
    t_data data;

    init_data(&data);
    if (!parse_args(argc, argv, &data))
    {
        printf("Usage: %s [mandelbrot | julia <real> <imaginary>]\n", argv[0]);
        printf("Julia set parameters must be between -2.0 and 2.0\n");
        return (1);
    }
    draw_fractal(&data);  
    mlx_hook(data.win, 17, 0, (int (*)())close_window, &data);
    mlx_key_hook(data.win, key_hook, &data);
    mlx_mouse_hook(data.win, mouse_event, &data);
    mlx_loop(data.mlx);
    return (0);
}  