
#include "../header.h"

int	press_actions(int keycode, t_mlx *root)
{
	if (keycode == 65307)
		mlx_loop_end(root->mlx);

	if ((keycode == RIGHT || keycode == RIGHTA))
		root->player->turn_direction += 1;
		// root->player->x += 1;
	if ((keycode == LEFT || keycode == LEFTA))
		root->player->turn_direction -= 1;
	if ((keycode == UP || keycode == UPA))
		root->player->walk_direction += 1;
	if ((keycode == DOWN || keycode == DOWNA))
		root->player->walk_direction -= 1;
	// if (!root->player->img)
	// 	invalid_map_error(root, NULL);
	// mlx_put_image_to_window(root->mlx, root->mlx_win, root->player->img,
	// 	root->player->x, root->player->y);
	return (0);
}

int	release_actions(int keycode, t_mlx *root)
{
	if (keycode == 65307)
		mlx_loop_end(root->mlx);

	if ((keycode == RIGHT || keycode == RIGHTA))
		root->player->turn_direction = 0;
	if ((keycode == LEFT || keycode == LEFTA))
		root->player->turn_direction = 0;
	if ((keycode == UP || keycode == UPA))
		root->player->walk_direction = 0;
	if ((keycode == DOWN || keycode == DOWNA))
		root->player->walk_direction = 0;
	update_image(root);
	return (0);
}