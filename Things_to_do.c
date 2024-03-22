1.  Change the name of the struct to t_fractol in the 
library and in the main in fractol.c

2. Change to printf 

// 3. Modify comments over the functions (rm ***)

4. Remove fractals and its components

5. Remove all comments

6. Check all 42 Headers

7. Remove functionality left and right mouse clicks. Also in help_msg

8. Change content of help_messages \t, \e....

8.1 Change ft_putendl_fd to ft_printf, e se non funzionare usa ft_putstr

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

15. Handle negative vaules resulting out of the modulo operation
            void	set_color_graphic(t_fractol *fractal_data, int color)

16. Why some specific functions are static, so confined to the "file", and do not need to
    be included into the header file, and other are included in the header file?

17. Remove functionality of Julia_shift
            int	mouse_event(int keycode, int x, int y, t_fractol *mlx)
            int	julia_shift(int x, int y, t_fractol *fractal_data)
            keys.h
            fractol.h

18. Change all doubles to float