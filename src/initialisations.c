#include "../header.h"


int	there_is_wall(t_mlx *root, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if ((x < 0 || x >= WINDOW_WIDTH) || (y < 0 || y >= WINDOW_HEIGHT))
		return (TRUE);
	if (root->map[map_y][map_x] != 0 && root->map[map_y][map_x] != '1')
		return (FALSE);
	return (TRUE);
}

// static void	malloc_struct(t_mlx *root)
// {
// 	root->maps = malloc(sizeof(t_img));
// 	if (root->maps == 0)
// 		malloc_error(root);
// }




static void	init_struct(t_mlx *root, char *path)
{
	root->path = path;
	root->map = NULL;
	root->data_map = NULL;
	root->is_player = 0;
	root->win_width = WINDOW_WIDTH;
	root->win_height = WINDOW_HEIGHT;
	root->mlx = 0;
	root->texture_up = NULL;
	root->texture_down = NULL;
	root->texture_left = NULL;
	root->texture_right = NULL;
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
	player->rotation_angle = PI / 2;
	player->walk_speed = 4;
	player->turn_speed = 4 * (PI / 180);
	root->player = player;
	return (1);
}


void move_player(t_mlx *root)
{
	root->player->rotation_angle += root->player->turn_direction * root->player->turn_speed;
    float move_step = root->player->walk_direction * root->player->walk_speed;

    float new_x = root->player->x + cos(root->player->rotation_angle) * move_step;
    float new_y = root->player->y + sin(root->player->rotation_angle) * move_step;
	if (!there_is_wall(root, new_x, new_y))
	{
		root->player->x = new_x;
		root->player->y = new_y;
	}
}

int update_image(t_mlx *root) 
{
	raycast(root);
	generate_3d_projection(root);
	move_player(root);
	free(root->rays);
	return (1);
}

void	print_tab(t_mlx *root)
{
	int i = 0;

	while (root->map[i])
	{
		printf("%s\n", root->map[i]);
		i++;
	}
}

void	game_driver(char *path)
{
	t_mlx	*root;

	root = malloc(sizeof(t_mlx));
	if (root == 0)
		malloc_error(root);
	// malloc_struct(root);
	init_struct(root, path);
	root->mlx = mlx_init();
	root->mlx_win = mlx_new_window(root->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	init_player(root, 0, 0);
	map_parsing(root, path);
	map_parsing2(root);
	setup_textures(root);
	print_tab(root);
	mlx_hook(root->mlx_win, 2, 1L << 0, press_actions, root); // key press
	mlx_hook(root->mlx_win, 3, 1L << 1, release_actions, root); // key release
	mlx_loop_hook(root->mlx, update_image, root);
	mlx_hook(root->mlx_win, 17, 1L << 17, mlx_loop_end, root->mlx);
	mlx_loop(root->mlx);
	kill_all(root);
}
