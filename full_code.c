// FRACTOL.H FILE:

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include "keys.h"
# include <stdio.h>
# include <math.h>

# define WIDTH 900
# define HEIGHT 900
# define MAX_ITERATIONS 60

# define MANDELBROT 1
# define JULIA 2

typedef struct t_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int		set;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	double	kr;
	double	ki;
	double	sx;
	double	rx;
	double	fx;
	int		*palette;
	int		color_pattern;
	int		color;
}	t_fractol;

/*  Fractal Sets   */
int		mandelbrot(double cr, double ci);
int		julia(t_fractol *fractal_data, double zr, double zi);

/*  Draw Fractal	*/
void	render(t_fractol *fractal_data);
static void	set_pixel_color(t_fractol *fractal_data, int x, int y, int color);// ?????
static int	calculate_fractal(t_fractol *fractal_data, double pr, double pi); // ?????


/* Colors	*/
void	set_color_mono(t_fractol *fractal_data, int color);
void	set_color_multiple(t_fractol *fractal_data, int colors[4], int n);
void	set_color_zebra(t_fractol *fractal_data, int color);
void	set_color_triad(t_fractol *fractal_data, int color);
void	set_color_tetra(t_fractol *fractal_data, int color);
int		get_percent_color(int color, double percent);
static int	interpolate(int startcolor, int endcolor, double fraction); // ??????
static void	fill_color_stripe(t_fractol *fractal_data, int color, int stripe); // ??????


/*  Events   */
int		mouse_event(int keycode, int x, int y, t_fractol *mlx);
static void	move(t_fractol *fractal_data, double distance, char direction); // ?????????
static void	zoom(t_fractol *fractal_data, double zoom); // ??????



/* Initialization */
void	clean_init(t_fractol *fractal_data);
static void	init_img(t_fractol *fractal_data);
void	reinit_img(t_fractol *fractal_data);
void	init(t_fractol *fractal_data);
void	get_complex_layout(t_fractol *fractal_data);

/*  Utils   */
int		end_fractol(t_fractol *mlx);
void	clean_exit(int error_code, t_fractol *fractal_data);
int		msg(char *str1, char *str2, int errno);
void	help_msg(t_fractol *fractal_data);
void	print_controls(void);

/*Parsing ???????*/

static int	skip_space_sign_0x(char *color);
static int	ft_atox_color(t_fractol *fractal_data, char *color);
void	get_color(t_fractol *fractal_data, int ac, char **av);
static int	skip_space_sign(char *str, int *is_neg);
double	ft_atof(char *str);

/*Help message ???????*/

void	print_fractal_options(void);
void	print_color_options(void);
void	print_controls(void);
void	help_msg(t_fractol *fractal_data);


/*Main code ???????*/

static int	type_cmp(char *av, char *str, char c, char n);
static void	get_set(t_fractol *fractal_data, char **av);
static void	get_julia_starting_values(t_fractol *fractal_data, int ac, char **av);
static void	handle_args(t_fractol *fractal_data, int ac, char **av);


#endif

// KEYS.H FILE:

#ifndef KEYS_H
# define KEYS_H

# define EVENT_CLOSE_BTN 17
# define KEY_ESC 65307
# define KEY_ONE 49
# define KEY_TWO 50
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5

#endif

// UTILS.H FILE:

#include "fractol.h"

void	clean_exit(int exit_code, t_fractol *fractal_data)
{
	if (!f)
		exit(exit_code);
	if (fractal_data->palette)
		free(fractal_data->palette);
	if (fractal_data->img)
		mlx_destroy_image(fractal_data->mlx, fractal_data->img);
	if (fractal_data->win && fractal_data->mlx)
		mlx_destroy_window(fractal_data->mlx, fractal_data->win);
	if (fractal_data->mlx)
	{
		mlx_loop_end(fractal_data->mlx);
		mlx_destroy_display(fractal_data->mlx);
		free(fractal_data->mlx);
	}
	exit(exit_code);
}

int	msg(char *str1, char *str2, int errno)
{
	ft_printf("Fractol: ");
	ft_printf(str1);
	ft_printf(str2);
	return (errno);
}

int	end_fractol(t_fractol *mlx)
{
	clean_exit(0, mlx);
	return (0);
}

// RENDER.C FILE:

#include "fractol.h"

static void	set_pixel_color(t_fractol *fractal_data, int x, int y, int color)
{
		fractal_data->buf[x * 4 + y * WIDTH * 4] = color;
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}

static int	calculate_fractal(t_fractol *fractal_data, double pr, double pi)
{
	int	nb_iter;

	if (fractal_data->set == MANDELBROT)
		nb_iter = mandelbrot(pr, pi);
	else if (fractal_data->set == JULIA)
		nb_iter = julia(f, pr, pi);
	return (nb_iter);
}

void	render(t_fractol *fractal_data)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	int		nb_iter;

	mlx_clear_window(fractal_data->mlx, fractal_data->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = fractal_data->min_r + (double)x * (fractal_data->max_r - fractal_data->min_r) / WIDTH;
			pi = fractal_data->max_i + (double)y * (fractal_data->min_i - fractal_data->max_i) / HEIGHT;
			nb_iter = calculate_fractal(f, pr, pi);
			set_pixel_color(f, x, y, fractal_data->palette[nb_iter]);
		}
	}
	mlx_put_image_to_window(fractal_data->mlx, fractal_data->win, fractal_data->img, 0, 0);
}

// PARSE_ARGS.C FILE:

#include "fractol.h"

static int	skip_space_sign_0x(char *color)
{
	int	i;

	i = 0;
	while (ft_isspace(color[i]))
		i++;
	if (color[i] == '+')
		i++;
	if (color[i] == '0' && (color[i + 1]
			&& (color[i + 1] == 'x' || color[i] == 'X')))
		i = i + 2;
	return (i);
}

static int	ft_atox_color(t_fractol *fractal_data, char *color)
{
	int	i;
	int	x;
	int	n;

	n = 0;
	i = 0;
	i = skip_space_sign_0x(color);
	x = 0;
	while (color[i] && ft_ishexdigit(color[i]))
	{
		if (ft_isdigit(color[i]))
			n = (n * 16) + (color[i] - '0');
		else
			n = (n * 16) + (ft_toupper(color[i]) - 'A' + 10);
		i++;
		x++;
	}
	if (x == 6 && !color[i])
		return (n);
	else
		help_msg(f);
	return (-1);
}

void	get_color(t_fractol *fractal_data, int ac, char **av)
{
	if (fractal_data->set == JULIA && ac == 5)
		fractal_data->color = ft_atox_color(f, av[4]);
	else if (fractal_data->set != JULIA && ac == 3)
		fractal_data->color = ft_atox_color(f, av[2]);
	if (ac == 2 || (fractal_data->set == JULIA && ac == 4))
		fractal_data->color = 0x9966FF;
}

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

double	ft_atof(char *str)
{
	int		i;
	double	nb;
	int		is_neg;
	double	div;

	nb = 0;
	div = 0.1;
	is_neg = 1;
	i = skip_space_sign(str, &is_neg);
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

// INITIALIZATION.C FILE:

#include "fractol.h"

void	clean_init(t_fractol *fractal_data)
{
	fractal_data->mlx = NULL;
	fractal_data->win = NULL;
	fractal_data->img = NULL;
	fractal_data->buf = NULL;
	fractal_data->set = -1; 
	fractal_data->min_r = 0;
	fractal_data->max_r = 0;
	fractal_data->min_i = 0;
	fractal_data->max_i = 0;
	fractal_data->kr = 0;
	fractal_data->ki = 0;
	fractal_data->sx = 0;
	fractal_data->rx = 0;
	fractal_data->fx = 0;
	fractal_data->palette = NULL;
	fractal_data->color_pattern = -1;
	fractal_data->color = 0;
}

void	get_complex_layout(t_fractol *fractal_data)
{
	if (fractal_data->set == MANDELBOX)
	{
		fractal_data->min_r = -4.0;
		fractal_data->max_r = 4.0;
		fractal_data->min_i = -4.0;
		fractal_data->max_i = fractal_data->min_i + (fractal_data->max_r - fractal_data->min_r) * HEIGHT / WIDTH;
	}
	else if (fractal_data->set == JULIA)
	{
		fractal_data->min_r = -2.0;
		fractal_data->max_r = 2.0;
		fractal_data->min_i = -2.0;
		fractal_data->max_i = fractal_data->min_i + (fractal_data->max_r - fractal_data->min_r) * HEIGHT / WIDTH;
	}
	else
	{
		fractal_data->min_r = -2.0;
		fractal_data->max_r = 1.0;
		fractal_data->max_i = -1.5;
		fractal_data->min_i = fractal_data->max_i + (fractal_data->max_r - fractal_data->min_r) * HEIGHT / WIDTH;
	}
}

static void	init_img(t_fractol *fractal_data)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buf;

	fractal_data->palette = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	if (!(fractal_data->palette))
		clean_exit(msg("error initializing color scheme.", "", 1), f);
	fractal_data->img = mlx_new_image(fractal_data->mlx, WIDTH, HEIGHT);
	if (!(fractal_data->img))
		clean_exit(msg("image creation error.", "", 1), f);
	buf = mlx_get_data_addr(fractal_data->img, &pixel_bits, &line_bytes, &endian);
	fractal_data->buf = buf;
}

void	reinit_img(t_fractol *fractal_data)
{
	if (fractal_data->mlx && fractal_data->img)
		mlx_destroy_image(fractal_data->mlx, fractal_data->img);
	if (fractal_data->palette)
		free(fractal_data->palette);
	if (fractal_data->buf)
		fractal_data->buf = NULL;
	init_img(f);
}

void	init(t_fractol *fractal_data)
{
	fractal_data->mlx = mlx_init();
	if (!fractal_data->mlx)
		clean_exit(msg("MLX: error connecting to mlx.", "", 1), f);
	fractal_data->win = mlx_new_window(fractal_data->mlx, WIDTH, HEIGHT, "Fractol");
	if (!fractal_data->win)
		clean_exit(msg("MLX: error creating window.", "", 1), f);
	fractal_data->sx = 2.0;
	fractal_data->rx = 0.5;
	fractal_data->fx = 1.0;
	get_complex_layout(f);
	color_shift(f);
}

// HELP_MSG.C FILE:

#include "fractol.h"

void	print_fractal_options(void)
{
	ft_printf("~~~~~  Available Fractals  ~~~~~");
	ft_printf("Which fractal would you like to view?");
	ft_printf("\tM - Mandelbrot");
	ft_printf("\tJ - Julia");
	ft_printf("\e[36mUsage example:\t");
	ft_printf("./fractol <type>\n\t\t./fractol M\e[0m")
	ft_printf("\nFor Julia, you may specify starting values for the\n");
	ft_printf("initial fractal shape. Values must be between\n");
	ft_printf("-2.0 and 2.0 and must contain a decimal point.");
	ft_printf("\e[36mUsage example:\t");
	ft_printf("./fractol J\n\t\t./fractol J 0.285 0.01\e[0m");
}

void	print_color_options(void)
{
	ft_printf("\n~~~~~ Color Display ~~~~~");
	ft_printf("Pick a display color by providing a hexadecimal code.");
	ft_printf("The hex color code must be formatted as RRGGBB:");
	ft_printf("\tWhite:\tFFFFFF\t\tBlack:\t000000");
	ft_printf("\tRed:\tFF0000\t\tGreen:\t00FF00");
	ft_printf("\tBlue:\t0000FF\t\tYellow:\tFFFF00");
	ft_printf("Other interesting colors:");
	ft_printf("\tPurple:\t9933FF\t\tOrange:\tCC6600");
	ft_printf("\tPink:\tFF3399\t\tTurquoise: 00FF80\t");
	ft_printf("\e[36mUsage example:\t");
	ft_printf("./fractol <type> <color>");
	ft_printf("\t\t./fractol M 0066FF\e[0m");
	ft_printf("\nFor Julia, you can only specify colors after");
	ft_printf("the starting values.");
	ft_printf("\e[36mUsage example:\t");
	ft_printf("./fractol J 0.285 0.01 CC6600\e[0m");
}

void	print_controls(void)
{
	ft_printf("\n~~~~~  Controls  ~~~~~");
	ft_printf("scroll wheel\tzoom in and out.");
	ft_printf("1, 2\t\t to switch fractals.");
	ft_printf("ESC or close window\tquit fract'ol.");
	ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void	help_msg(t_fractol *fractal_data)
{
	print_fractal_options();
	print_color_options();
	clean_exit(EXIT_FAILURE, f);
}

// FRACTOL.C FILE:

#include "fractol.h"

static int	type_cmp(char *av, char *str, char c, char n)
{
	int	i;

	i = 0;
	while (av[i])
	{
		av[i] = ft_tolower(av[i]);
		i++;
	}
	if (!ft_strncmp(av, str, ft_strlen(str) + 1))
		return (1);
	else if (av[1] == '\0' && (av[0] == c || av[0] == n))
		return (1);
	return (0);
}

static void	get_set(t_fractol *fractal_data, char **av)
{
	if (type_cmp(av[1], "mandelbrot", 'm', '1'))
		fractal_data->set = MANDELBROT;
	else if (type_cmp(av[1], "julia", 'j', '2'))
		fractal_data->set = JULIA;
	else
		help_msg(f);
}

static void	get_julia_starting_values(t_fractol *fractal_data, int ac, char **av)
{
	if (fractal_data->set != JULIA || ac == 2)
	{
		fractal_data->kr = -0.766667;
		fractal_data->ki = -0.090000;
		return ;
	}
	if (ac == 3)
		help_msg(f);
	if (!ft_strchr(av[2], '.'))
		help_msg(f);
	if (!ft_strchr(av[3], '.'))
		help_msg(f);
	fractal_data->kr = ft_atof(av[2]);
	fractal_data->ki = ft_atof(av[3]);
	if (fractal_data->kr > 2.0 || fractal_data->kr < -2.0)
		help_msg(f);
	if (fractal_data->ki >= 2.0 || fractal_data->ki <= -2.0)
		help_msg(f);
}

static void	handle_args(t_fractol *fractal_data, int ac, char **av)
{
	get_set(f, av);
	if (fractal_data->set != JULIA && ac > 3)
		help_msg(f);
	else if (fractal_data->set == JULIA && ac > 5)
		help_msg(f);
	get_julia_starting_values(f, ac, av);
	get_color(f, ac, av);
}

int	main(int ac, char **av)
{
	t_fractol	fractal_data;

	if (ac < 2)
		help_msg(&fractal_data);
	clean_init(&fractal_data);
	handle_args(&fractal_data, ac, av);
	init(&fractal_data);
	render(&fractal_data);
	print_controls();
	mlx_hook(f.win, EVENT_CLOSE_BTN, 0, end_fractol, &fractal_data);
	mlx_mouse_hook(f.win, mouse_event, &fractal_data);
	mlx_loop(f.mlx);
}

// EVENTS.C FILE:

#include "fractol.h"

static void	zoom(t_fractol *fractal_data, double zoom)
{
	double	center_r;
	double	center_i;

	center_r = fractal_data->min_r - fractal_data->max_r;
	center_i = fractal_data->max_i - fractal_data->min_i;
	fractal_data->max_r = fractal_data->max_r + (center_r - zoom * center_r) / 2;
	fractal_data->min_r = fractal_data->max_r + zoom * center_r;
	fractal_data->min_i = fractal_data->min_i + (center_i - zoom * center_i) / 2;
	fractal_data->max_i = fractal_data->min_i + zoom * center_i;
}

static void	move(t_fractol *fractal_data, double distance, char direction)
{
	double	center_r;
	double	center_i;

	center_r = fractal_data->max_r - fractal_data->min_r;
	center_i = fractal_data->max_i - fractal_data->min_i;
	if (direction == 'R')
	{
		fractal_data->min_r += center_r * distance;
		fractal_data->max_r += center_r * distance;
	}
	else if (direction == 'L')
	{
		fractal_data->min_r -= center_r * distance;
		fractal_data->max_r -= center_r * distance;
	}
	else if (direction == 'D')
	{
		fractal_data->min_i -= center_i * distance;
		fractal_data->max_i -= center_i * distance;
	}
	else if (direction == 'U')
	{
		fractal_data->min_i += center_i * distance;
		fractal_data->max_i += center_i * distance;
	}
}

int	mouse_event(int keycode, int x, int y, t_fractol *mlx)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(mlx, 0.5);
		x -= WIDTH / 2;
		y -= HEIGHT / 2;
		if (x < 0)
			move(mlx, (double)x * -1 / WIDTH, 'L');
		else if (x > 0)
			move(mlx, (double)x / WIDTH, 'R');
		if (y < 0)
			move(mlx, (double)y * -1 / HEIGHT, 'U');
		else if (y > 0)
			move (mlx, (double)y / HEIGHT, 'D');
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom(mlx, 2);
	else
		return (0);
	render(mlx);
	return (0);
}

// JULIA.C FILE:

#include "fractol.h"

int	julia(t_fractol *fractal_data, double zr, double zi)
{
	int		n;
	double	tmp;

	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zi * zi + zr * zr) > 4.0)
			break ;
		tmp = 2 * zr * zi + fractal_data->ki;
		zr = zr * zr - zi * zi + fractal_data->kr;
		zi = tmp;
		n++;
	}
	return (n);
}

// MANDELBROT.C FILE:

#include "fractol.h"

int	mandelbrot(double cr, double ci)
{
	int		n;
	double	zr;
	double	zi;
	double	tmp;

	zr = 0;
	zi = 0;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		tmp = 2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
		n++;
	}
	return (n);
}

// COLOR_INTERPOLATED.C FILE:

#include "fractol.h"

static int	interpolate(int startcolor, int endcolor, double fraction)
{
	int	start_rgb[3];
	int	end_rgb[3];

	start_rgb[0] = ((startcolor >> 16) & 0xFF);
	start_rgb[1] = ((startcolor >> 8) & 0xFF);
	start_rgb[2] = ((startcolor >> 0) & 0xFF);
	end_rgb[0] = ((endcolor >> 16) & 0xFF);
	end_rgb[1] = ((endcolor >> 8) & 0xFF);
	end_rgb[2] = ((endcolor >> 0) & 0xFF);
	start_rgb[0] = (end_rgb[0] - start_rgb[0]) * fraction + start_rgb[0];
	start_rgb[1] = (end_rgb[1] - start_rgb[1]) * fraction + start_rgb[1];
	start_rgb[2] = (end_rgb[2] - start_rgb[2]) * fraction + start_rgb[2];
	return (0xFF << 24 | start_rgb[0] << 16 | start_rgb[1] << 8 | start_rgb[2]);
}

void	set_color_mono(t_fractol *fractal_data, int color)
{
	int		i;
	int		j;
	double	fraction;
	int		color1;
	int		color2;

	color1 = 0x000000;
	color2 = color;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while (j < MAX_ITERATIONS / 2)
		{
			fraction = (double)j / (MAX_ITERATIONS / 2);
			fractal_data->palette[i + j] = interpolate(color1, color2, fraction);
			j++;
		}
		color1 = color2;
		color2 = 0xFFFFFF;
		i += j;
	}
	fractal_data->palette[MAX_ITERATIONS -1] = 0;
}

void	set_color_multiple(t_fractol *fractal_data, int colors[4], int n)
{
	int		i;
	int		j;
	int		x;
	double	fraction;

	i = 0;
	x = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while ((i + j) < MAX_ITERATIONS && j < (MAX_ITERATIONS / (n - 1)))
		{
			fraction = (double)j / (MAX_ITERATIONS / (n - 1));
			fractal_data->palette[i + j] = interpolate(colors[x], colors[x + 1], fraction);
			j++;
		}
		x++;
		i += j;
	}
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

// COLOR_STRIPED.C FILE:

#include "fractol.h"

static void	fill_color_stripe(t_fractol *fractal_data, int color, int stripe)
{
	int	i;

	i = 0;
	while (i < MAX_ITERATIONS)
	{
		fractal_data->palette[i] = color;
		i += stripe;
	}
}

int	get_percent_color(int color, double percent)
{
	int		rgb[3];
	int		trgb[3];
	double	percentage;

	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
	percentage = (percent / 100) * 256;
	trgb[0] = (rgb[0] + percentage) - 256;
	trgb[1] = (rgb[1] + percentage) - 256;
	trgb[2] = (rgb[2] + percentage) - 256;
	return (0xFF << 24 | trgb[0] << 16 | trgb[1] << 8 | trgb[2]);
}

void	set_color_zebra(t_fractol *fractal_data, int color)
{
	int	color2;

	color2 = get_percent_color(color, 50);
	fill_color_stripe(f, color, 1);
	fill_color_stripe(f, color2, 2);
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

void	set_color_triad(t_fractol *fractal_data, int color)
{
	int		triad[2];

	triad[0] = get_percent_color(color, 33);
	triad[1] = get_percent_color(color, 66);
	fill_color_stripe(f, color, 1);
	fill_color_stripe(f, triad[0], 2);
	fill_color_stripe(f, triad[1], 3);
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

void	set_color_tetra(t_fractol *fractal_data, int color)
{
	int	tetra[3];

	tetra[0] = get_percent_color(color, 25);
	tetra[1] = get_percent_color(color, 50);
	tetra[2] = get_percent_color(color, 75);
	fill_color_stripe(f, color, 1);
	fill_color_stripe(f, tetra[0], 2);
	fill_color_stripe(f, tetra[1], 3);
	fill_color_stripe(f, tetra[2], 4);
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}
