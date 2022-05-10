#include "../header.h"

static void	malloc_tabs_of_xy(t_mlx *root)
{
	root->walls->x = malloc(sizeof(int) * root->walls->max);
	if (root->walls->x == 0)
		malloc_error(root);
	root->walls->y = malloc(sizeof(int) * root->walls->max);
	if (root->walls->y == 0)
		malloc_error(root);
}

static void	malloc_struct(t_mlx *root)
{
	root->player = malloc(sizeof(t_img));
	if (root->player == 0)
		malloc_error(root);
	root->maps = malloc(sizeof(t_img));
	if (root->maps == 0)
		malloc_error(root);
	root->walls = malloc(sizeof(t_tuple));
	if (root->walls == 0)
		malloc_error(root);
}

static void	init_struct(t_mlx *root)
{
	root->is_player = 0;
	root->walls->max = 0;
	root->win_width = 0;
	root->win_height = 0;
	root->mlx = 0;
	root->player->img = 0;
	root->player->img = 0;
	root->walls->y = 0;
	root->walls->x = 0;
}

void init_img_test(t_mlx *root)
{
	root->player->img = mlx_new_image(root->mlx, WINDOW_WIDHT, WINDOW_HEIGHT);
	root->player->addr = mlx_get_data_addr(root->player->img, &root->player->bits_per_pixel, &root->player->line_length,
								&root->player->endian);	
}

void	my_mlx_pixel_put(t_mlx *root, int x, int y, int color)
{
	char	*dst;

	dst = root->player->addr + (y * root->player->line_length + x * (root->player->bits_per_pixel / 8));

	*(unsigned int*)dst = color;
}



int	init_player(t_mlx *root, int x, int y)
{
	t_img *player;


	player = root->player;
	player->x = x;
	player->y = y;
	player->height = 10;
	player->width = 10;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = PI / 2;
	player->walk_speed = 50;
	player->turn_speed = 45 * (PI / 180);


	return (1);
}

void render_player(t_mlx *root)
{
	// mlx_pixel_put(root->mlx, root->mlx_win, root->player->x, root->player->y, 0x00FF0000);
	int i;
	int j;

	i = -1;
	while (++i < root->player->width)
	{
		j = -1;
		while (++j < root->player->height)
			mlx_pixel_put(root->mlx, root->mlx_win, root->player->x + i, root->player->y + j, 0x00FF0000);
	// 			mlx_pixel_put(root, root->player->x + i, root->player->y + j, 0x00FF0000);	
	}
		i = 40;
	while (--i > root->player->width)
			mlx_pixel_put(root->mlx, root->mlx_win, root->player->x + i, root->player->y, 0x00FF0000);
			// mlx_pixel_put(root, root->player->x + i, root->player->y, 0x00FF0000);	
	// mlx_put_image_to_window(root->mlx, root->mlx_win, root->player->img, 0, 0);
}

int update_player(t_mlx *root) 
{
    root->player->rotation_angle += root->player->turn_direction * root->player->turn_speed;
    float moveStep = root->player->walk_direction * root->player->walk_speed;

    float newPlayerX = root->player->x+ cos(root->player->rotation_angle) * moveStep;
    float newPlayerY = root->player->y + sin(root->player->rotation_angle) * moveStep;

    root->player->x = newPlayerX;
    root->player->y = newPlayerY;
	// render_player(root);
	return (1);
}



void	game_driver(char *path)
{
	t_mlx	*root;

	root = malloc(sizeof(t_mlx));
	if (root == 0)
		malloc_error(root);
	malloc_struct(root);
	init_struct(root);
	map_parsing(root, path);
	malloc_tabs_of_xy(root);
	root->mlx = mlx_init();
	root->mlx_win = mlx_new_window(root->mlx, WINDOW_WIDHT,
			WINDOW_HEIGHT, "cub3D");
	init_img_test(root);
	init_player(root, WINDOW_WIDHT / 2, WINDOW_HEIGHT / 2);
	render_player(root);

	// map_drawer(root, path);
	mlx_hook(root->mlx_win, 2, 1L << 0, moove_player, root); // key press
	mlx_hook(root->mlx_win, 3, 1L << 1, stop_player, root); // key release
	mlx_hook(root->mlx_win, 17, 1L << 17, mlx_loop_end, root->mlx);
	mlx_loop_hook(root->mlx, update_player, root);
	mlx_loop(root->mlx);
	// kill_all(root);
}
