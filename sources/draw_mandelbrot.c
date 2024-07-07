/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:59:24 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/07 18:00:17 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void draw_mandelbrot(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_mandelbrot(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_mandelbrot2(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_mandelbrot2(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_mandelbrot3(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_mandelbrot3(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_mandelbrot4(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            pixel_mandelbrot4(data, x, y);
            x++;
        }
        y++;
    }
}
