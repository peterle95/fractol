/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:30:15 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/29 17:03:18 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Cleans up resources and exits the program
int	exit_program(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx_connect, data->img);
	if (data->window)
		mlx_destroy_window(data->mlx_connect, data->window);
	if (data->mlx_connect)
	{
		mlx_destroy_display(data->mlx_connect);
		free(data->mlx_connect);
	}
	exit(0);
}
