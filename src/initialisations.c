#include "../header.h"

// static void	malloc_tabs_of_xy(t_mlx *root)
// {
// 	root->walls->x = malloc(sizeof(int) * root->walls->max);
// 	if (root->walls->x == 0)
// 		malloc_error(root);
// 	root->walls->y = malloc(sizeof(int) * root->walls->max);
// 	if (root->walls->y == 0)
// 		malloc_error(root);
// 	root->collectible->x = malloc(sizeof(int) * root->collectible->max);
// 	if (root->collectible->x == 0)
// 		malloc_error(root);
// 	root->collectible->y = malloc(sizeof(int) * root->collectible->max);
// 	if (root->collectible->y == 0)
// 		malloc_error(root);
// 	root->enemies->x = malloc(sizeof(int) * root->enemies->max);
// 	if (root->collectible->x == 0)
// 		malloc_error(root);
// 	root->enemies->y = malloc(sizeof(int) * root->enemies->max);
// 	if (root->collectible->y == 0)
// 		malloc_error(root);
// }

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




void	game_driver(char *path)
{
	t_mlx	*root;

	root = malloc(sizeof(t_mlx));
	if (root == 0)
		malloc_error(root);
	malloc_struct(root);
	init_struct(root);
	map_parsing(root, path);
	// malloc_tabs_of_xy(root);
	root->mlx = mlx_init();
	root->mlx_win = mlx_new_window(root->mlx, IMG_BITS * root->win_width,
			IMG_BITS * root->win_height, "cub3D");
	// map_drawer(root, path);
	// mlx_hook(root->mlx_win, 2, 1L << 0, moove_player, root);
	mlx_hook(root->mlx_win, 17, 1L << 17, mlx_loop_end, root->mlx);
	mlx_loop(root->mlx);
	// kill_all(root);
}
