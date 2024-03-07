/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:49:19 by pmolzer           #+#    #+#             */
/*   Updated: 2024/03/07 22:14:06 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* skip_space_sign_0x:
	Skips spaces, '+' sign character and '0x' or '0X'
	to parse hexadecimal color code strings.
*/
static int	skip_space_sign_0x(char *color)
{
	int	i;

	i = 0;
	while (ft_isspace(color[i]))
	/*iterates as long as the character at color[i] is a space using ft_isspace. 
	It increments i to skip leading spaces.*/
		i++;
	if (color[i] == '+')
	/*If the character at i is a +, 
	it's skipped by incrementing i again (positive signs are allowed but ignored).*/
		i++;
	if (color[i] == '0' && (color[i + 1]
			&& (color[i + 1] == 'x' || color[i] == 'X')))
		i = i + 2;
		/*inally, it checks if the character at i is 0 and the next character (color[i + 1]) 
		is either x or X (case-insensitive). If so, it skips both characters 
		by setting i to i + 2.*/
	return (i);
}

/* ft_atox_color:
	---> Translates a hexadecimal color code string into an integer.
	Valid: "RRGGBB", "0XRRGGBB", "rrggbb", "   +rrggbb"
	Invalid: "-RRGGBB" "RRGGBB-", "RR GG BB"
	If the string is not a valid hex color code, an error is displayed.
	Returns the converted int. -1 if an error occured.
*/
static int	ft_atox_color(t_fractol *fractal_data, char *color)
{
	int	i;
	/*Initialized by calling skip_space_sign_0x to handle leading spaces, signs,
	 and the optional 0x prefix.*/
	int	x;
	/*The variable x keeps track of the number of characters processed within the 
	actual color code part of the string.
	Validation: 
	After the loop, the function checks if x is exactly equal to 6. 
	A valid hexadecimal color code should have 6 digits (representing the 
	red, green, and blue components). If x is not 6, it implies an invalid color code format, 
	and the function raises an error.*/
	int	n;
	/*n is initialized to 0 to store the final color value.
*/

	n = 0;
	// i = 0;
	i = skip_space_sign_0x(color);
	x = 0;
	while (color[i] && ft_ishexdigit(color[i]))
	/*loop iterates while the character at i is not null and is a valid hexadecimal 
	digit using ft_ishexdigit.*/
	{
		if (ft_isdigit(color[i]))
			n = (n * 16) + (color[i] - '0');
		else
			n = (n * 16) + (ft_toupper(color[i]) - 'A' + 10);
		i++;
		x++;
	/*If the character is a digit (0-9), it's converted to the corresponding 
	numerical value (0-9) and added to n after shifting n left by 4 bits 
	(equivalent to multiplying by 16) using bitwise operations.
	Otherwise, it's assumed to be an uppercase letter (A-F) and converted to 
	its numerical value (10-15) by subtracting 'A' and adding 10, then added to n 
	with the same left shift.
	i is incremented to move to the next character.
	x is incremented to keep track of the number of characters processed.*/
	}
	if (x == 6 && !color[i])
		return (n);
	/*After the loop, if x is exactly 6 (representing 6 hexadecimal digits) and the next 
	character is null (meaning the string ends after the color code), the function returns 
	the converted integer n.*/
	else
		help_msg(f);
	return (-1);
}

/* get_color:
	The function aims to:

	Get the color option provided as an argument: 
	It checks if the user specified a color when running the program.
	Set a default color if none is provided: 
	If no color is specified, the function sets a default value.
*/
void	get_color(t_fractol *fractal_data, int ac, char **av)
{
	if (fractal_data->set == JULIA && ac == 5)
		fractal_data->color = ft_atox_color(f, av[4]);
	else if (fractal_data->set != JULIA && ac == 3)
		fractal_data->color = ft_atox_color(f, av[2]);
	if (ac == 2 || (fractal_data->set == JULIA && ac == 4))
		fractal_data->color = 0x9966FF;
}

/* skip_space_sign:
	Skips spaces, '+' and '-' sign characters and sets the
	is_neg variable if a '-' sign is detected.
	Used to parse strings representing float values for Julia.
*/
static int	skip_space_sign(char *str, int *is_neg)
{
	int	i;

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

/* ft_atof:
	Converts a string into a float (decimal number). Used to parse
	Julia starting values given as program arguments.
	Returns the converted double, or -42 in case of error (Julia accepts
	values between 2.0 and -2.0 only)
*/
double	ft_atof(char *str)
{
	int		i;
	/*Loop counter (initialized to the first non-whitespace character after handling sign)*/
	double	nb;
	/* Stores the converted number (initialized to 0)*/
	int		is_neg;
	/*Tracks whether the number is negative (initialized to 1, assuming positive initially)*/
	double	div;
	/*Stores a decimal divisor (initialized to 0.1, used for handling decimal places)*/
	
	nb = 0;
	div = 0.1;
	is_neg = 1;
	i = skip_space_sign(str, &is_neg);
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
	{
		nb = (nb * 10.0) + (str[i] - '0');
		i++;
	/*The loop iterates while str[i] is a valid digit and not a decimal point.
	  Inside the loop:
	  nb is multiplied by 10 to accommodate the next digit.
	  The character str[i] is converted to its numerical value by subtracting '0'.
	  The result is added to nb..*/
	}
	if (str[i] == '.')
		i++;
	/*If the current character is a decimal point (.), i is incremented again*/
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = nb + ((str[i] - '0') * div);
		div *= 0.1;
		i++;
	/*Another loop iterates while str[i] is a valid digit.
	  Inside the loop:
	  nb is incremented by adding the difference between the current digit and 
	  '0' multiplied by the current div value (representing the decimal place).
	  div is further divided by 10 (adjusting the decimal place for the next digit).*/
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-42);
		/*If str[i] is not a digit after the decimal point, it indicates an invalid format, 
		and the function returns -42 to signal an error.
		
		The choice of -42 is arbitrary and serves as a unique error code to indicate that the conversion failed. 
		This value isn't a valid Julia set parameter and can be easily distinguished from a successful conversion result.
		Any other non-valid Julia set parameter could technically be used. However, it's crucial to choose a value that:
		Doesn't fall within the valid range of Julia set parameters (-2.0 to 2.0) 
		to avoid confusion with a successful conversion.
		Preferably, isn't a special value already used for other purposes within the program to maintain clarity and 
		avoid potential conflicts.
		Therefore, while other non-valid values could work, -42 offers a clear and readily distinguishable error 
		code without introducing ambiguity in the context of Julia set parameter validation.*/
	return (nb * is_neg);
}
