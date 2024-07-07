/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:14:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/07 18:03:06 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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

int	julia_checker(t_data *data, char argc, char **argv)
{
	data->fractal_type = JULIA;
	if (argc == 4)
	{
		data->julia_ci = convert_float(argv[2]);
		data->julia_cr = convert_float(argv[3]);
		if (data->julia_ci == -42.0 || data->julia_cr == -42.0
			|| data->julia_ci < -2.0 || data->julia_ci > 2.0
			|| data->julia_cr < -2.0 || data->julia_cr > 2.0)
			return (0);
	}
	else if (argc != 2)
		return (0);
	return (0);
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
		printf("Error: Invalid arguments\n");
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
