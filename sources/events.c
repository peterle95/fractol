/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:22 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/04 18:38:43 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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

void apply_movement(t_data *data, double move_x, double move_y)
{
    double range_re = data->max_re - data->min_re;
    double range_im = data->max_im - data->min_im;

    data->min_re += move_x * range_re;
    data->max_re += move_x * range_re;
    data->min_im += move_y * range_im;
    data->max_im += move_y * range_im;

    draw_fractal(data);
}

// think about assigning 0.1 to MOVE_STEP. And the keys as well
int key_hook(int keycode, t_data *data)
{
    double move_x = 0;
    double move_y = 0;
    int fractal_changed = 0;

    if (keycode == 65307) // ESC key
        exit_program(data);
    else if (keycode == 65361) // Key Left
        move_x = -0.1;
    else if (keycode == 65363) // Key Right
        move_x = 0.1;
    else if (keycode == 65362) // Key UP
        move_y = -0.1;
    else if (keycode == 65364) // Key Down
        move_y = 0.1;
    else if(keycode >= 49 && keycode <= 56) // Keys between 1-8
    {
        data->fractal_type = keycode - 49;
        fractal_changed = 1;
    }
    else
        return (0);

    // Apply movement
    /* if (move_x != 0 || move_y != 0)
    {
        double range_re = data->max_re - data->min_re;
        double range_im = data->max_im - data->min_im;
        data->min_re += move_x * range_re;
        data->max_re += move_x * range_re;
        data->min_im += move_y * range_im;
        data->max_im += move_y * range_im;
        fractal_changed = 1; // set to 1 because we need to redraw after movement
    } */
    if (move_x != 0 || move_y != 0)
        apply_movement(data, move_x, move_y);
    if(fractal_changed != 0)
        draw_fractal(data);
    return (0);
}