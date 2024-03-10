1.  Change the name of the struct to t_fractol in the 
library and in the main in fractol.c

2. Change to printf 

// 3. Modify comments over the functions (rm ***)

4. Remove fractals and its components

5. Remove all comments

6. Check all 42 Headers

7. Remove functionality left and right mouse clicks. Also in help_msg

8. Change content of help_messages \t, \e....

9. Change typ_cpm name, also change c to character, and n to number

10. Change name of handle_args to handle_arguments

11. Check if the title of the window is called "Fractol - 42 project": 
            void	init(t_fractol *fracta l_data)

12. Play around with the colors: 
            void	color_shift(t_fractol *fractal_data)

13. Change trgb to target_rbg.
            int	get_percent_color(int color, double percent)

14. Play around with the percentage of the color
            void	set_color_tetra(t_fractol *fractal_data, int color)
            void	set_color_triad(t_fractol *fractal_data, int color)
            void	set_color_zebra(t_fractol *fractal_data, int color)