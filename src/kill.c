#include "../header.h"

static void	kill_window(t_mlx *root)
{
	if (root->mlx)
	{
		if (root->texture_up)
			mlx_destroy_image(root->mlx, root->texture_up);
		if (root->texture_down)
			mlx_destroy_image(root->mlx, root->texture_down);
		if (root->texture_right)
			mlx_destroy_image(root->mlx, root->texture_right);
		if (root->texture_left)
			mlx_destroy_image(root->mlx, root->texture_left);
		if (root->mlx_win)
			mlx_destroy_window(root->mlx, root->mlx_win);
		if (root->mlx)
		mlx_destroy_display(root->mlx);
	}
}

void	kill_all(t_mlx *root)
{
	int i;
	
	kill_window(root);
	i = -1;
	if (root->map)
	{
		while (root->map[++i])
			free(root->map[i]);
		free(root->map);
	}
	free(root->ea);
	free(root->so);
	free(root->no);
	free(root->we);
	if (root->player)
		free(root->player);
	if (root->mlx)
		free(root->mlx);
	if (root)
		free(root);
	exit(0);
}