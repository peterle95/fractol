#include "../includes/fractol.h"

void	pixel_mandelbrot(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot(cr, ci);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_mandelbrot2(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot(cr, ci);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_mandelbrot3(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot(cr, ci);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}

void	pixel_mandelbrot4(t_data *data, int x, int y)
{
	double	cr;
	double	ci;
	int		color;

	cr = calculate_cr(data, x);
	ci = calculate_ci(data, y);
	color = color_mandelbrot(cr, ci);
	mlx_pixel_put(data->mlx, data->win, x, y, color);
}