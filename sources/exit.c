/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:30:15 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/12 23:03:55 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	exit_program(t_data *data)
{
	mlx_destroy_window(data->mlx_connect, data->window);
	/*
   This function is used to destroy the window created by MiniLibX. It's important because:
   
   - It frees up the memory allocated for the window.
     It removes the window from the X server.
	 It helps prevent memory leaks.*/
	mlx_destroy_display(data->mlx_connect);
	/*This function is used to close the connection to the X server. It's necessary because:
	It frees resources associated with the display connection.
	It helps ensure a clean shutdown of the X client (your program).
	It prevents potential resource leaks on the X server side.*/
	free(data->mlx_connect);
	/*
	This line is crucial for proper memory management:
	- It frees the memory allocated for the MLX connection.
	- Prevents memory leaks by releasing resources that are no longer needed.
	- Ensures that all dynamically allocated memory associated with the MLX connection is properly deallocated.
	- Failure to free this memory could lead to resource leaks and potential system instability.
	*/

	exit(0); // part of the stdlib.h
	/*
	This function call is essential for clean program termination:
	- It terminates the program immediately with a successful status code (0).
	- Ensures that the program exits gracefully after all resources have been freed.
	- Prevents the program from continuing execution after cleanup, which could lead to undefined behavior.
	- The status code 0 indicates to the operating system that the program completed successfully.
	- It's part of the C standard library (stdlib.h), making it a portable way to end the program.
	*/
}
