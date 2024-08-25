/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:30:15 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/25 22:00:54 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Cleans up resources and exits the program
int	exit_program(t_data *data)
{
	mlx_destroy_window(data->mlx_connect, data->window);
	mlx_destroy_display(data->mlx_connect);
	free(data->mlx_connect);
	exit(0);
}
