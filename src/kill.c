#include "../header.h"

static void	kill_window(t_mlx *root)
{
	if (root->mlx)
	{
		mlx_destroy_image(root->mlx, root->texture_up);
		mlx_destroy_image(root->mlx, root->texture_down);
		mlx_destroy_image(root->mlx, root->texture_right);
		mlx_destroy_image(root->mlx, root->texture_left);
		mlx_destroy_window(root->mlx, root->mlx_win);
		mlx_destroy_display(root->mlx);
	}
}


void	kill_all(t_mlx *root)
{
	kill_window(root);
	if (root->player)
		free(root->player);
	if (root->map)
		free(root->map);
	if (root->mlx)
		free(root->mlx);
	if (root)
		free(root);
	exit(0);
}