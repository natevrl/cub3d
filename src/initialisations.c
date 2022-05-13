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



void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}


void put_rectangle(t_mlx *root, int x, int y)
{
	int i = -1;
	int j;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
			// mlx_pixel_put(root->mlx, root->mlx_win, x + i, y + j, 0x000000AA);
			my_mlx_pixel_put(root->maps, x + i, y + j, 0x000000AA);

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
	player->walk_speed = 5;
	player->turn_speed = 5 * (PI / 180);


	return (1);
}




void draw_player(t_mlx *root)
{
	int i;
	int j;

	i = -1;
	while (++i < root->player->width)
	{
		j = -1;
		while (++j < root->player->height)
			// mlx_pixel_put(root->mlx, root->mlx_win, root->player->x + i, root->player->y + j, 0x00FF0000);
			my_mlx_pixel_put(root->maps, root->player->x + i, root->player->y + j, 0x00FF0000);
	}
	i = -1;
	while (++i < 40)
		my_mlx_pixel_put(root->maps, root->player->x + cos(root->player->rotation_angle) * i, root->player->y + sin(root->player->rotation_angle) * i, 0x00FF0000);
}

void redraw(t_mlx *root)
{
	t_img img;
	img.img = mlx_new_image(root->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	root->maps = &img;
	draw_map(root);
	draw_player(root);
	mlx_put_image_to_window(root->mlx, root->mlx_win, img.img, 0, 0);
	mlx_destroy_image(root->mlx, img.img);

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
	redraw(root);
	raycast(root);

	render_rays(root);
	// draw_player(root);
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
	redraw(root);
	mlx_hook(root->mlx_win, 2, 1L << 0, press_actions, root); // key press
	mlx_hook(root->mlx_win, 3, 1L << 1, release_actions, root); // key release
	mlx_loop_hook(root->mlx, update_image, root);
	mlx_hook(root->mlx_win, 17, 1L << 17, mlx_loop_end, root->mlx);
	mlx_loop(root->mlx);
	// kill_all(root);
}
