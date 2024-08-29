/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:37:22 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/29 17:02:17 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// Validates if the input string is a valid Julia set parameter
int	validate_julia(char *str)
{
	int		i;
	int		digits_after_point;

	i = 0;
	digits_after_point = 0;
	while (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (1);
	i++;
	if (str[i] != '.')
		return (1);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		digits_after_point++;
		i++;
	}
	if (digits_after_point < 1 || digits_after_point > 3)
		return (1);
	return (0);
}
