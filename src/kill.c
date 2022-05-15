#include "../header.h"

static void	kill_window(t_mlx *root)
{
	if (root->mlx)
	{
		if (root->player->img)
			mlx_destroy_image(root->mlx, root->player->img);
		if (root->maps->img)
			mlx_destroy_image(root->mlx, root->maps->img);
		if (root->mlx_win)
			mlx_destroy_window(root->mlx, root->mlx_win);
		mlx_destroy_display(root->mlx);
	}
}


void	kill_all(t_mlx *root)
{
	kill_window(root);
	if (root->player)
		free(root->player);
	if (root->maps)
		free(root->maps);
	if (root->mlx)
		free(root->mlx);
	if (root)
		free(root);
	exit(0);
}