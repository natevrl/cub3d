#include "../header.h"


int map[NUMBER_MAP_ROWS][NUMBER_MAP_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int mapHasWallAt(float x, float y) 
{
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return TRUE;
    }
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

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

static void	init_struct(t_mlx *root, char *path)
{
	root->path = path;
	root->is_player = 0;
	root->walls->max = 64;
	root->win_width = 0;
	root->win_height = 0;
	root->mlx = 0;
	root->player->img = 0;
	root->player->img = 0;
	root->walls->y = 0;
	root->walls->x = 0;
	root->maps->width = WINDOW_WIDTH;
	root->maps->height = WINDOW_HEIGHT;
}

void init_rays(t_mlx *root)
{
	// int i = -1;

	root->rays = malloc(sizeof(t_rays) * NUMBER_OF_RAYS);
	// while (++i < NUMBER_OF_RAYS)
	// {
	// 	// printf("%d\n", i);
	// 	// root->rays[i] = malloc(sizeof(t_rays));
	// 	root->rays[i]->ray_angle = 0;
	// 	root->rays[i]->wall_hit_x = 0;
	// 	root->rays[i]->wall_hit_y = 0;
	// 	root->rays[i]->distance = 0;
	// 	root->rays[i]->was_hit_vertical = 0;
	// 	root->rays[i]->is_ray_facing_up = 0;
	// 	root->rays[i]->is_ray_facing_down = 0;
	// 	root->rays[i]->is_ray_facing_left = 0;
	// 	root->rays[i]->is_ray_facing_right = 0;
	// 	root->rays[i]->wallHitContent = 0;
	// }
}

void init_main_image(t_mlx *root)
{
	root->player->img = mlx_new_image(root->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	root->player->addr = mlx_get_data_addr(root->player->img, &root->player->bits_per_pixel, &root->player->line_length,
								&root->player->endian);	
}

int	init_player(t_mlx *root, int x, int y)
{
	t_img *player;


	player = root->player;
	player->x = x;
	player->y = y;
	player->height = 1;
	player->width = 1;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = PI / 2;
	player->walk_speed = 0.2;
	player->turn_speed = 0.2 * (PI / 180);


	return (1);
}

void put_rectangle(t_mlx *root, int x, int y)
{
	int i = -1;
	int j;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
			mlx_pixel_put(root->mlx, root->mlx_win, x + i, y + j, 0x000000AA);
	}


}

int	draw_map(t_mlx *root)
{
	int			i;
	int			j;
	int			x;
	int f = -1;
	static int first_draw = 1;
	int	y = 0;

	i = -1;
	x = 0;
	while (++i < NUMBER_MAP_ROWS)
	{
		j = -1;
		x = 0;
		while (++j < NUMBER_MAP_COLS)
		{
			if (map[i][j] == 1)
			{
				put_rectangle(root, x, y);
				// put_wall(root, x, y);
				if (first_draw == 1)
				{
					root->walls->x[++f] = x;
					root->walls->y[f] = y;
				}
			}
			x += TILE_SIZE;
		}
	y += TILE_SIZE;
	}
	first_draw = 0;
	return (1);
}

void render_player(t_mlx *root)
{
	int i;
	int j;

	i = -1;
	while (++i < root->player->width)
	{
		j = -1;
		while (++j < root->player->height)
				mlx_pixel_put(root->mlx, root->mlx_win, root->player->x + i, root->player->y + j, 0x00FF0000);
	}
	i = -1;
	while (++i < 40)
		mlx_pixel_put(root->mlx, root->mlx_win, root->player->x + cos(root->player->rotation_angle) * i, root->player->y + sin(root->player->rotation_angle) * i, 0x00FF0000);
}

void move_player(t_mlx *root)
{
	root->player->rotation_angle += root->player->turn_direction * root->player->turn_speed;
    float move_step = root->player->walk_direction * root->player->walk_speed;

    float new_x = root->player->x + cos(root->player->rotation_angle) * move_step;
    float new_y = root->player->y + sin(root->player->rotation_angle) * move_step;

    root->player->x = new_x;
    root->player->y = new_y;
}

int update_image(t_mlx *root) 
{

	move_player(root);
	raycast(root);
	// map_drawer(root);
	// draw_map(root);

	mlx_put_image_to_window(root->mlx, root->mlx_win, root->player->img, 0, 0);
	render_rays(root);
	render_player(root);
	return (1);
}



void	game_driver(char *path)
{
	t_mlx	*root;

	root = malloc(sizeof(t_mlx));
	if (root == 0)
		malloc_error(root);
	malloc_struct(root);
	init_struct(root, path);
	// map_parsing(root);
	malloc_tabs_of_xy(root);
	root->mlx = mlx_init();
	root->mlx_win = mlx_new_window(root->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	init_player(root, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	init_main_image(root);
	init_rays(root);
	draw_map(root);

	mlx_hook(root->mlx_win, 2, 1L << 0, press_actions, root); // key press
	mlx_hook(root->mlx_win, 3, 1L << 1, release_actions, root); // key release
	mlx_loop_hook(root->mlx, update_image, root);
	mlx_hook(root->mlx_win, 17, 1L << 17, mlx_loop_end, root->mlx);
	mlx_loop(root->mlx);
	// kill_all(root);
}
