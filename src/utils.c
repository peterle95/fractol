/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:46:43 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/07 22:14:53 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* clean_exit:
	Destroys the window, the MLX image and the MLX instance,
	and frees the color palette, before ending the MLX loop
	and destroying the display. Exits the process with the provided
	exit code.
*/
void	clean_exit(int exit_code, t_fractol *fractal_data)
{
	if (!fractal_data)
		exit(exit_code);
	if (fractal_data->palette)
		free(fractal_data->palette);
	if (fractal_data->img)
		mlx_destroy_image(fractal_data->mlx, fractal_data->img);
	if (fractal_data->win && fractal_data->mlx)
		mlx_destroy_window(fractal_data->mlx, fractal_data->win);
	if (fractal_data->mlx)
	{
		mlx_loop_end(fractal_data->mlx);
		mlx_destroy_display(fractal_data->mlx);
		free(fractal_data->mlx);
	}
	exit(exit_code);
}

/* msg:
	Displays an error message to the standard error.
	Returns the provided error number.
*/
int	msg(char *str1, char *str2, int errno)
{
	ft_putstr_fd("Fractol: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	return (errno);
}

/* end_fractol:
	Exits cleanly from the program.
	This function is registered to an MLX hook: whenever the
	user hits the right button, this function will be called
	automatically.
*/
int	end_fractol(t_fractol *mlx)
{
	clean_exit(0, mlx);
	return (0);
}
