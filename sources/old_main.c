/* void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    (void)data; 
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int     close_window(t_data *data)
{
    (void)data; 
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
}

int     key_hook(int keycode, t_data *data)
{
    (void)data;  // Add this line if 'data' is unused
    if (keycode == 53) // ESC key
        close_window(data);
    printf("Key pressed: %d\n", keycode);
    return (0);
}

int     mouse_hook(int button, int x, int y, t_data *data)
{
    (void)data;  // This line tells the compiler that we're intentionally not using 'data'
    printf("Mouse button %d pressed at (%d, %d)\n", button, x, y);
    return (0);
}

int     main(void)
{
    t_data  data;

    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Fractol");
    if (!data.win)
        return (1);

    data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    // Draw a simple pattern
    for (int y = 0; y < WIN_HEIGHT; y++)
    {
        for (int x = 0; x < WIN_WIDTH; x++)
        {
            int color = (x * 256 / WIN_WIDTH) | ((y * 256 / WIN_HEIGHT) << 8);
            my_mlx_pixel_put(&data, x, y, color);
        }
    }

    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

    mlx_hook(data.win, 17, 0, close_window, &data);  // Handle window close button
    mlx_key_hook(data.win, key_hook, &data);
    mlx_mouse_hook(data.win, mouse_hook, &data);

    mlx_loop(data.mlx);

    return (0);
} */