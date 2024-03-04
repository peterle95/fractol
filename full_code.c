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
# define BURNING_SHIP 3
# define TRICORN 4
# define MANDELBOX 5

typedef struct s_fractol
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

int		mandelbrot(double cr, double ci);
int		julia(t_fractol *f, double zr, double zi);
int		burning_ship(double cr, double ci);
int		tricorn(double cr, double ci);
int		mandelbox(t_fractol *f, double cr, double ci);

void	render(t_fractol *f);
int		julia_shift(int x, int y, t_fractol *f);

void	color_shift(t_fractol *f);
void	set_color_mono(t_fractol *f, int color);
void	set_color_multiple(t_fractol *f, int colors[4], int n);
void	set_color_zebra(t_fractol *f, int color);
void	set_color_triad(t_fractol *f, int color);
void	set_color_tetra(t_fractol *f, int color);
void	set_color_opposites(t_fractol *f, int color);
void	set_color_contrasted(t_fractol *f, int color);
void	set_color_graphic(t_fractol *f, int color);
int		get_percent_color(int color, double percent);

int		key_event(int keycode, t_fractol *mlx);
int		mouse_event(int keycode, int x, int y, t_fractol *mlx);

void	clean_init(t_fractol *f);
void	reinit_img(t_fractol *f);
void	init(t_fractol *f);
void	get_complex_layout(t_fractol *f);
void	get_color(t_fractol *f, int ac, char **av);
double	ft_atof(char *str);

int		end_fractol(t_fractol *mlx);
void	clean_exit(int error_code, t_fractol *f);
int		msg(char *str1, char *str2, int errno);
void	help_msg(t_fractol *f);
void	print_controls(void);

#endif

#ifndef KEYS_H
# define KEYS_H

# define EVENT_CLOSE_BTN 17
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_SPACE 32
# define KEY_ONE 49
# define KEY_TWO 50
# define KEY_THREE 51
# define KEY_FOUR 52
# define KEY_FIVE 53
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_WHEEL_BTN 3
# define MOUSE_BTN 1
# define MOUSE_BTN_2 3
# define KEY_K 107

#endif

// FRACTOL.C

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
	else if (type_cmp(av[1], "burning ship", 'b', '3'))
		fractal_data->set = BURNING_SHIP;
	else if (type_cmp(av[1], "tricorn", 't', '4'))
		fractal_data->set = TRICORN;
	else if (type_cmp(av[1], "mandelbox", 'x', '5'))
		fractal_data->set = MANDELBOX;
	else
		help_msg(fractal_data);
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
		help_msg(fractal_data);
	if (!ft_strchr(av[2], '.'))
		help_msg(fractal_data);
	if (!ft_strchr(av[3], '.'))
		help_msg(fractal_data);
	fractal_data->kr = ft_atof(av[2]);
	fractal_data->ki = ft_atof(av[3]);
	if (fractal_data->kr > 2.0 || fractal_data->kr < -2.0)
		help_msg(fractal_data);
	if (fractal_data->ki >= 2.0 || fractal_data->ki <= -2.0)
		help_msg(fractal_data);
}

static void	handle_args(t_fractol *fractal_data, int ac, char **av)
{
	get_set(f, av);
	if (fractal_data->set != JULIA && ac > 3)
		help_msg(fractal_data);
	else if (fractal_data->set == JULIA && ac > 5)
		help_msg(fractal_data);
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
	mlx_hook(fractal_data.win, EVENT_CLOSE_BTN, 0, end_fractol, &fractal_data);
	mlx_key_hook(fractal_data.win, key_event, &fractal_data);
	mlx_mouse_hook(fractal_data.win, mouse_event, &fractal_data);
	mlx_loop(f.mlx);
}

// UTILS.C

void	clean_exit(int exit_code, t_fractol *f)
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
	ft_putstr_fd("Fractol: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	return (errno);
}

int	end_fractol(t_fractol *mlx)
{
	clean_exit(0, mlx);
	return (0);
}

// RENDER.C

static void	set_pixel_color(t_fractol *f, int x, int y, int color)
{
		fractal_data->buf[x * 4 + y * WIDTH * 4] = color;
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
		fractal_data->buf[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}

static int	calculate_fractal(t_fractol *f, double pr, double pi)
{
	int	nb_iter;

	if (fractal_data->set == MANDELBROT)
		nb_iter = mandelbrot(pr, pi);
	else if (fractal_data->set == JULIA)
		nb_iter = julia(f, pr, pi);
	else if (fractal_data->set == BURNING_SHIP)
		nb_iter = burning_ship(pr, pi);
	else if (fractal_data->set == TRICORN)
		nb_iter = tricorn(pr, pi);
	else if (fractal_data->set == MANDELBOX)
		nb_iter = mandelbox(f, pr, pi);
	return (nb_iter);
}

void	render(t_fractol *f)
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

// PARSE_ARGUMENTS.C

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

// INITIALIZATION.C

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
		clean_exit(msg("error initializing color scheme.", "", 1), fractal_data);
	fractal_data->img = mlx_new_image(fractal_data->mlx, WIDTH, HEIGHT);
	if (!(fractal_data->img))
		clean_exit(msg("image creation error.", "", 1), fractal_data);
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
	init_img(fractal_data);
}

void	init(t_fractol *fractal_data)
{
	fractal_data->mlx = mlx_init();
	if (!fractal_data->mlx)
		clean_exit(msg("MLX: error connecting to mlx.", "", 1), fractal_data);
	fractal_data->win = mlx_new_window(fractal_data->mlx, WIDTH, HEIGHT, "Fractol");
	if (!fractal_data->win)
		clean_exit(msg("MLX: error creating window.", "", 1), fractal_data);
	fractal_data->sx = 2.0;
	fractal_data->rx = 0.5;
	fractal_data->fx = 1.0;
	get_complex_layout(fractal_data);
	color_shift(fractal_data);
}

// HELP_MSG.C

void	print_fractal_options(void)
{
	ft_putendl_fd("+===============  Available Fractals  ===============+", 1);
	ft_putendl_fd("Which fractal would you like to view?", 1);
	ft_putendl_fd("\tM - Mandelbrot", 1);
	ft_putendl_fd("\tJ - Julia", 1);
	ft_putendl_fd("\tB - Burning Ship", 1);
	ft_putendl_fd("\tT - Tricorn", 1);
	ft_putendl_fd("\tX - Mandelbox", 1);
	ft_putendl_fd("\e[36mUsage example:\t./fractol <type>\n\t\t./fractol M\e[0m", 1);
	ft_putstr_fd("\nFor Julia, you may specify starting values for the\n", 1);
	ft_putstr_fd("initial fractal shape. Values must be between\n", 1);
	ft_putendl_fd("-2.0 and 2.0 and must contain a decimal point.", 1);
	ft_putendl_fd("\e[36mUsage example:\t", 1);
	ft_putendl_fd("./fractol J\n\t\t./fractol J 0.285 0.01\e[0m", 1);
}

void	print_color_options(void)
{
	ft_putendl_fd("\n+===============  Color Display  ====================+", 1);
	ft_putendl_fd("Pick a display color by providing a hexadecimal code.", 1);
	ft_putendl_fd("The hex color code must be formatted as RRGGBB:", 1);
	ft_putendl_fd("\tWhite:\tFFFFFF\t\tBlack:\t000000", 1);
	ft_putendl_fd("\tRed:\tFF0000\t\tGreen:\t00FF00", 1);
	ft_putendl_fd("\tBlue:\t0000FF\t\tYellow:\tFFFF00", 1);
	ft_putendl_fd("Other interesting colors:", 1);
	ft_putendl_fd("\tPurple:\t9933FF\t\tOrange:\tCC6600", 1);
	ft_putendl_fd("\tPink:\tFF3399\t\tTurquoise: 00FF80\t", 1);
	ft_putstr_fd("\e[36mUsage example:\t", 1);
	ft_putendl_fd("./fractol <type> <color>", 1);
	ft_putendl_fd("\t\t./fractol M 0066FF\e[0m", 1);
	ft_putendl_fd("\nFor Julia, you can only specify colors after", 1);
	ft_putendl_fd("the starting values.", 1);
	ft_putstr_fd("\e[36mUsage example:\t", 1);
	ft_putendl_fd("./fractol J 0.285 0.01 CC6600\e[0m", 1);
}

void	print_controls(void)
{
	ft_putendl_fd("\n+===============  Controls  =========================+", 1);
	ft_putendl_fd("WASD or arrow keys\tmove view.", 1);
	ft_putendl_fd("+/- or scroll wheel\tzoom in and out.", 1);
	ft_putendl_fd("Spacebar\t\tchange color schemes.", 1);
	ft_putendl_fd("Left click\t\tshift Julia set [Julia only].", 1);
	ft_putendl_fd("1, 2, 3, 4, 5\t\tswitch fractals.", 1);
	ft_putendl_fd("ESC or close window\tquit fract'ol.", 1);
	ft_putendl_fd("+====================================================+\n", 1);
}

void	help_msg(t_fractol *fractal_data)
{
	ft_putendl_fd("\n+====================================================+", 1);
	ft_putendl_fd("|                     FRACT'OL                       |", 1);
	ft_putendl_fd("+====================================================+\n", 1);
	print_fractal_options();
	print_color_options();
	clean_exit(EXIT_FAILURE, f);
}

// EVENTS.C

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

static int	key_event_extend(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_ONE && mlx->set != MANDELBROT)
		mlx->set = MANDELBROT;
	else if (keycode == KEY_TWO && mlx->set != JULIA)
		mlx->set = JULIA;
	else if (keycode == KEY_THREE && mlx->set != BURNING_SHIP)
		mlx->set = BURNING_SHIP;
	else if (keycode == KEY_FOUR && mlx->set != TRICORN)
		mlx->set = TRICORN;
	else if (keycode == KEY_FIVE && mlx->set != MANDELBOX)
		mlx->set = MANDELBOX;
	else
		return (1);
	get_complex_layout(mlx);
	render(mlx);
	return (0);
}

int	key_event(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_ESC)
	{
		end_fractol(mlx);
		return (0);
	}
	else if (keycode == KEY_PLUS)
		zoom(mlx, 0.5);
	else if (keycode == KEY_MINUS)
		zoom(mlx, 2);
	else if (keycode == KEY_UP || keycode == KEY_W)
		move(mlx, 0.2, 'U');
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move(mlx, 0.2, 'D');
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		move(mlx, 0.2, 'L');
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		move(mlx, 0.2, 'R');
	else if (keycode == KEY_SPACE)
		color_shift(mlx);
	else if (!key_event_extend(keycode, mlx))
		return (1);
	else
		return (1);
	render(mlx);
	return (0);
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
	else if (keycode == MOUSE_BTN)
	{
		if (mlx->set == JULIA)
			julia_shift(x, y, mlx);
	}
	else
		return (0);
	render(mlx);
	return (0);
}

// COLOR.C 

static void	color_shift_special(t_fractol *fractal_data)
{
	int	alt_color;

	if (fractal_data->color == 0xFFFFFF)
		alt_color = 0xCCCCCC;
	else
		alt_color = fractal_data->color;
	if (fractal_data->color_pattern == 5)
		set_color_contrasted(fractal_data, alt_color);
	else if (fractal_data->color_pattern == 6)
		set_color_opposites(fractal_data, fractal_data->color);
	else if (fractal_data->color_pattern == 7)
		set_color_graphic(fractal_data, fractal_data->color);
	else if (fractal_data->color_pattern == 8)
		set_color_multiple(fractal_data, (int [8]){0xFF0000, 0xFF7F00, 0xFFFF00,
			0x00FF00, 0x0000FF, 0x4B0082, 0x9400D3, 0xFFFFFF}, 8);
}

static void	color_shift_striped(t_fractol *fractal_data)
{
	if (fractal_data->color_pattern == 2)
		set_color_zebra(fractal_data, fractal_data->color);
	else if (fractal_data->color_pattern == 3)
		set_color_triad(fractal_data, fractal_data->color);
	else if (fractal_data->color_pattern == 4)
		set_color_tetra(fractal_data, fractal_data->color);
	else
		color_shift_special(fractal_data);
}

void	color_shift(t_fractol *fractal_data)
{
	int	alt_color;

	fractal_data->color_pattern = (fractal_data->color_pattern + 1) % 9;
	reinit_img(fractal_data);
	if (fractal_data->color == 0x000000)
		alt_color = 0x333333;
	else
		alt_color = fractal_data->color;
	if (fractal_data->color_pattern == 0)
		set_color_mono(fractal_data, alt_color);
	else if (fractal_data->color_pattern == 1)
		set_color_multiple(fractal_data, (int [4]){0x000000, alt_color,
			get_percent_color(fractal_data->color, 50), 0xFFFFFF}, 4);
	else
		color_shift_striped(fractal_data);
}

// TRICORN.C

int	tricorn(double cr, double ci)
{
	int		n;
	double	zr;
	double	zi;
	double	tmp;

	zr = cr;
	zi = ci;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		tmp = -2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
		n++;
	}
	return (n);
}

// MANDELBRIT.C

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

// MANDELBOX.C

static double	box_fold(double v)
{
	if (v > 1)
		v = 2 - v;
	else if (v < -1)
		v = -2 - v;
	return (v);
}

static double	ball_fold(double r, double m)
{
	if (m < r)
		m = m / (r * r);
	else if (m < 1)
		m = 1 / (m * m);
	return (m);
}

int	mandelbox(t_fractol *fractal_data, double cr, double ci)
{
	int		n;
	double	vr;
	double	vi;
	double	mag;

	vr = cr;
	vi = ci;
	mag = 0;
	n = 0;
	while (n < MAX_ITERATIONS)
	{		
		vr = fractal_data->fx * box_fold(vr);
		vi = fractal_data->fx * box_fold(vi);
		mag = sqrt(vr * vr + vi * vi);
		vr = vr * fractal_data->sx * ball_fold(fractal_data->rx, mag) + cr;
		vi = vi * fractal_data->sx * ball_fold(fractal_data->rx, mag) + ci;
		if (sqrt(mag) > 2)
			break ;
		n++;
	}
	return (n);
}

// JULIA.C

int	julia_shift(int x, int y, t_fractol *fractal_data)
{
	fractal_data->kr = fractal_data->min_r + (double)x * (fractal_data->max_r - fractal_data->min_r) / WIDTH;
	fractal_data->ki = fractal_data->max_i + (double)y * (fractal_data->min_i - fractal_data->max_i) / HEIGHT;
	render(f);
	return (0);
}

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

// BURNING_SHIP.C

int	burning_ship(double cr, double ci)
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
		zr = fabs(zr);
		zi = fabs(zi);
		tmp = 2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
		n++;
	}
	return (n);
}

// COLOR_STRIPED.C

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
	fill_color_stripe(fractal_data, color, 1);
	fill_color_stripe(fractal_data, color2, 2);
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

void	set_color_triad(t_fractol *fractal_data, int color)
{
	int		triad[2];

	triad[0] = get_percent_color(color, 33);
	triad[1] = get_percent_color(color, 66);
	fill_color_stripe(fractal_data, color, 1);
	fill_color_stripe(fractal_data, triad[0], 2);
	fill_color_stripe(fractal_data, triad[1], 3);
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

void	set_color_tetra(t_fractol *fractal_data, int color)
{
	int	tetra[3];

	tetra[0] = get_percent_color(color, 25);
	tetra[1] = get_percent_color(color, 50);
	tetra[2] = get_percent_color(color, 75);
	fill_color_stripe(fractal_data, color, 1);
	fill_color_stripe(fractal_data, tetra[0], 2);
	fill_color_stripe(fractal_data, tetra[1], 3);
	fill_color_stripe(fractal_data, tetra[2], 4);
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

// COLOR_SPECIAL.C

void	set_color_opposites(t_fractol *fractal_data, int color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	i = -1;
	while (++i < MAX_ITERATIONS)
	{
		fractal_data->palette[i] = 0;
		r += i % 0xFF;
		g += i % 0xFF;
		b += i % 0xFF;
		fractal_data->palette[i] = 0xFF << 24 | r << 16 | g << 8 | b;
	}
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

void	set_color_contrasted(t_fractol *fractal_data, int color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	i = -1;
	while (++i < MAX_ITERATIONS)
	{
		fractal_data->palette[i] = 0;
		if (r != 0xFF)
			r += i % 0xFF;
		if (g != 0xFF)
			g += i % 0xFF;
		if (b != 0xFF)
			b += i % 0xFF;
		fractal_data->palette[i] = 0xFF << 24 | r << 16 | g << 8 | b;
	}
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

void	set_color_graphic(t_fractol *fractal_data, int color)
{
	int	i;
	int	rgb[3];

	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
	i = -1;
	while (rgb[0] < 0x33 || rgb[1] < 0x33 || rgb[2] < 0x33)
	{
		if (rgb[0] != 0xFF)
			rgb[0]++;
		if (rgb[1] != 0xFF)
			rgb[1]++;
		if (rgb[2] != 0xFF)
			rgb[2]++;
	}
	while (++i < MAX_ITERATIONS)
	{
		fractal_data->palette[i] = 0;
		rgb[0] -= i % 0xFF;
		rgb[1] -= i % 0xFF;
		rgb[2] -= i % 0xFF;
		fractal_data->palette[i] = 0xFF << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	}
	fractal_data->palette[MAX_ITERATIONS - 1] = 0;
}

// COLOR_INTRAPOLATED.C

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