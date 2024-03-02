/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:44:12 by pmolzer           #+#    #+#             */
/*   Updated: 2024/02/21 01:44:12 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define EVENT_CLOSE_BTN 17
# define KEY_ESC 65307
# define KEY_ONE 49
# define KEY_TWO 50
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5

#endif

/*1. #define EVENT_CLOSE_BTN 17

This defines a constant named EVENT_CLOSE_BTN and assigns it the value 
17.

This value might represent a specific event code
 or identifier associated with the "close button" 
 event in the windowing system being used 
 (likely MiniLibX based on the presence of mlx.h 
 in the previous header file).

When the program detects a close button click or window closure event,
 it might compare the received event code with EVENT_CLOSE_BTN to 
 determine the appropriate action (e.g., clean exit or prompt for 
 confirmation).

2. #define KEY_ESC 65307

This defines a constant named KEY_ESC and assigns it the value 65307.

This value likely represents the scan code (or virtual key code) for 
the Escape key on the keyboard.

In the mouse_event function of fractol.h, 
the program might check the pressed key code against KEY_ESC 
to handle specific actions when the Escape key is pressed 
(e.g., exit the program or display a help menu).

3-5. Key Definitions:

Similar to KEY_ESC, these lines define constants for other keyboard keys:
KEY_ONE for the number 1 key (49)
KEY_TWO for the number 2 key (50)
The program might use these constants to associate 
specific actions with these keys, potentially for 
changing the displayed fractal type, color palettes, or other settings.

6. #define MOUSE_WHEEL_UP 4

This defines a constant named MOUSE_WHEEL_UP and assigns it the value 4.

This value might represent an event code 
or identifier specific to the windowing system for
 a "mouse wheel up" event.

The mouse_event function could check for this 
code to handle zooming in or adjusting other parameters 
when the user scrolls the mouse wheel upwards.

7. #define MOUSE_WHEEL_DOWN 5

This defines a constant named MOUSE_WHEEL_DOWN and assigns it the value 5.

Similar to MOUSE_WHEEL_UP, this likely represents the event code for 
a "mouse wheel down" event.

The program might use this to handle zooming out or
 other adjustments triggered by scrolling the mouse wheel downwards.*/