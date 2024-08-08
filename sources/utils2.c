/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:37:22 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/08 14:40:49 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int validate_julia(char *str)
{
    int i = 0;
    int digits_after_point = 0;

    // Check for optional negative sign
    while (str[i] == '-' || str[i] == '+')
        i++;

    // There should be one digit before decimal point
    if (!ft_isdigit(str[i]))
        return (1);
    i++;

    // Check if after the first digit there is no decimal point returns 1
    if (str[i] != '.')
        return (1);
    i++;

    // Check for one to three digits after decimal point
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