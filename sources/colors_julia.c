/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_julia.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:54:10 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/06 21:08:12 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	color_julia(t_data *data, double zr, double zi)
{
	int		iterations;

	iterations = julia(zr, zi, data->julia_cr, data->julia_ci);
	return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}

int	color_julia2(t_data *data, double zr, double zi)
{
	int		iterations;

	iterations = julia(zr, zi, data->julia_cr, data->julia_ci);
	return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}

int	color_julia3(t_data *data, double zr, double zi)
{
	int		iterations;

	iterations = julia(zr, zi, data->julia_cr, data->julia_ci);
	return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}

int	color_julia4(t_data *data, double zr, double zi)
{
	int		iterations;

	iterations = julia(zr, zi, data->julia_cr, data->julia_ci);
	return (iterations * 0xFFFFFF / MAX_ITERATIONS);
}
