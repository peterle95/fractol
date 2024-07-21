/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:14:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/21 13:37:42 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	draw_fractal(t_data *data)
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
}

int julia_checker(t_data *data, int argc, char **argv)
{
    data->fractal_type = JULIA;
    if (argc == 4)
    {
        if (validate_julia(argv[2]) || validate_julia(argv[3]))
                return (1);
        data->julia_ci = convert_float(argv[2]);
        data->julia_cr = convert_float(argv[3]);
        if (data->julia_ci == -42.0 || data->julia_cr == -42.0)
            return (1);
        if (data->julia_ci < -2.0 || data->julia_ci > 2.0 || 
            data->julia_cr < -2.0 || data->julia_cr > 2.0)
                    return (1);
                return (0);
    }
    else
        return (1);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 2)
		return (0);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		if (argc > 2)
			return (0);
		else
			data->fractal_type = MANDELBROT;
	}
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		if (julia_checker(data, argc, argv) != 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_data(&data))
	{
		printf("Error: Failed to initialize\n");
		return (1);
	}
	if (!parse_args(argc, argv, &data))
	{
		print_usage();
		exit_program(&data);
		return (1);
	}
	draw_fractal(&data);
	mlx_hook(data.win, 17, 0, exit_program, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_mouse_hook(data.win, mouse_event, &data);
	mlx_loop(data.mlx);
	return (0);
}
