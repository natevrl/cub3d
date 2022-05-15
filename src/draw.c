#include "../header.h"

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

			if (root->map[i][j] == '1')
				put_rectangle(root, x, y);
			x += TILE_SIZE;
		}
	y += TILE_SIZE;
	}
	first_draw = 0;
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