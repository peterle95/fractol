/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:24 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/03 18:12:55 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void init_fractal(t_data *data)
{
    data->min_re = -2.0;
    data->max_re = 1.0;
    data->min_im = -1.5;
    data->max_im = data->min_im + (data->max_re - data->min_re) * WIN_HEIGHT / WIN_WIDTH;
    data->zoom = 1.0;
    data->julia_ci = 0.27;
    data->julia_cr = -0.7;
    // julia 0.27 -0.75
    //julia 0.15 -0.7
}

int init_data(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        return (0);

    data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Fract'ol");
    if (!data->win)
    {
        free(data->mlx);
        return (0);
    }

    data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!data->img)
    {
        mlx_destroy_window(data->mlx, data->win);
        free(data->mlx);
        return (0);
    }

    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
                                   &data->line_length, &data->endian);

    init_fractal(data);

    return (1);
}
