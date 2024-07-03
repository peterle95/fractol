/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:37 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/03 21:20:27 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;

	while ((s1[i] != '\0' && s2[i] != '\0') && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int    skip_space_and_sign(char *str, int *is_neg)
{
    int    i;

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            *is_neg *= -1;
        i++;
    }
    return (i);
}

/* convert_float:
    Converts a string into a float (decimal number). Used to parse
    Julia starting values given as program arguments.
    Returns the converted double, or -42 in case of error (Julia accepts
    values between 2.0 and -2.0 only)
*/
double    convert_float(char *str)
{
    int        i;
    double    nb;
    int        is_neg;
    double    div;

    nb = 0;
    div = 0.1;
    is_neg = 1;
    i = skip_space_and_sign(str, &is_neg);
    while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
    {
        nb = (nb * 10.0) + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
        i++;
    while (str[i] && ft_isdigit(str[i]))
    {
        nb = nb + ((str[i] - '0') * div);
        div *= 0.1;
        i++;
    }
    if (str[i] && !ft_isdigit(str[i]))
        return (-42);
    return (nb * is_neg);
}