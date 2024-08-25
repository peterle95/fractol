/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:37:22 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/25 21:57:44 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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
