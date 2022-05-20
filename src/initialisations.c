#include "../header.h"


int	there_is_wall(t_mlx *root, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if ((x < 0 || x >= (TILE_SIZE * root->x)) || (y < 0 || y >= (TILE_SIZE * root->y)))
		return (TRUE);
	if (root->map[map_y][map_x] != 0 && root->map[map_y][map_x] != '1')
		return (FALSE);
	return (TRUE);
}


static void	init_struct(t_mlx *root, char *path)
{
	root->path = path;
	root->map = NULL;
	root->data_map = NULL;
	root->is_player = 0;
	root->win_width = WINDOW_WIDTH;
	root->win_height = WINDOW_HEIGHT;
	root->mlx = 0;
	root->mlx_win = NULL;
	root->texture_up = NULL;
	root->texture_down = NULL;
	root->texture_left = NULL;
	root->texture_right = NULL;
	root->ea = NULL;
	root->we = NULL;
	root->so = NULL;
	root->no = NULL;
}


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}


int	init_player(t_mlx *root, int x, int y)
{
	t_img *player;

	player = malloc(sizeof(t_img));
	player->x = x;
	player->y = y;
	player->height = 1;
	player->width = 1;
	root->pos_p_x = 0;
	root->pos_p_y = 0;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->pas_chasse = 0;
	player->rota_angle = 0;
	player->walk_speed = 4;
	player->turn_speed = 4 * (PI / 180);
	root->player = player;
	return (1);
}

int update_image(t_mlx *root) 
{
	raycast(root);
	generate_3d_projection(root);
	move_player(root);
	free(root->rays);
	root->rays = NULL;
	return (1);
}

void	print_tab(t_mlx *root)
{
	int i = 0;

	while (root->map[i])
		i++;
}

void	game_driver(char *path)
{
	t_mlx	*root;

	root = malloc(sizeof(t_mlx));
	if (root == 0)
		malloc_error(root);
	init_struct(root, path);
	root->mlx = mlx_init();
	init_player(root, 0, 0);
	map_parsing(root, path);
	map_parsing2(root);
	stock_data(root);
	root->mlx_win = mlx_new_window(root->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	setup_textures(root);
	root->player->rota_angle += (root->player->turn_direction - 0.1) * root->player->turn_speed;
	mlx_hook(root->mlx_win, 2, 1L << 0, press_actions, root); // key press
	mlx_hook(root->mlx_win, 3, 1L << 1, release_actions, root); // key release
	mlx_loop_hook(root->mlx, update_image, root);
	mlx_hook(root->mlx_win, 17, 1L << 17, mlx_loop_end, root->mlx);
	mlx_loop(root->mlx);
	kill_all(root);
}
