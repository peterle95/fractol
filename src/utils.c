/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:46:43 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/08 15:53:32 by pmolzer          ###   ########.fr       */
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
		/*This line checks if the t_fractol pointer (fractal_data) is NULL. 
		If it is, it means the structure wasn't properly initialized, 
		and there's nothing to clean up. The function directly calls exit 
		with the provided exit_code.*/
	if (fractal_data->palette)
		free(fractal_data->palette);
		/*This line checks if fractal_data->palette is not NULL. 
		If it is not NULL, it means a color palette was allocated 
		using malloc or a similar function. The line calls free(fractal_data->palette) 
		to deallocate the memory associated with the palette, preventing memory leaks.*/
	if (fractal_data->img)
		mlx_destroy_image(fractal_data->mlx, fractal_data->img);
		/*the function checks if fractal_data->img is not NULL. 
		If it's not NULL, it means an MLX image (mlx_image_t) was created. 
		The line calls mlx_destroy_image from the MiniLibX library to properly 
		deallocate the image and its associated memory. It provides the mlx instance 
		(fractal_data->mlx) and the image pointer (fractal_data->img) as arguments.*/
	if (fractal_data->win && fractal_data->mlx)
		mlx_destroy_window(fractal_data->mlx, fractal_data->win);
		/*This line checks two conditions:
		fractal_data->win is not NULL, indicating a window was created.
		fractal_data->mlx is not NULL, indicating a valid MLX instance exists 
		(presumably used to create the window).
		If both conditions are true, the line calls mlx_destroy_window from 
		MiniLibX to destroy the window associated with the mlx instance 
		and the fractal_data->win pointer.*/
	if (fractal_data->mlx)
	{
		mlx_loop_end(fractal_data->mlx);
		mlx_destroy_display(fractal_data->mlx);
		free(fractal_data->mlx);
		/*This section handles deallocating resources associated with the MiniLibX library:
		mlx_loop_end(fractal_data->mlx): 
		If an MLX instance (fractal_data->mlx) exists, this line ends the main 
		event loop of MiniLibX, ensuring the program doesn't hang waiting for events.
		mlx_destroy_display(fractal_data->mlx): 
		This line destroys the MLX display associated with the mlx instance.
		free(fractal_data->mlx): 
		Finally, the line calls free to deallocate the memory 
		used by the mlx instance itself.*/
	}
	exit(exit_code);
	/*After all the cleanup tasks, the function calls exit(exit_code). 
	This ensures the program terminates with the provided exit_code.*/


	/*EXIT() IN C:
	The C exit () function is a standard library function (stdlib.h) used to 
	terminate the calling process. When exit () is called, any open file descriptor belonging
	to the process are close and any children of the process are inherited by process 1, int,
	and the process parent is sent a SIGCHLD signal.
	
	Syntax: 
	void exit(int status);
	
	Parameters:
	The exit() function in C only takes a single parameter "status" which is the exit code that
	is returned to the caller i.e. the operating system or parent process. There are two valid
	values we can use as the status each having a different meaning:
	- 0 or EXIT_SUCCESS
	- 1 or EXIT_FAILURE*/
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
