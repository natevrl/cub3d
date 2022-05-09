
#include "../header.h"

static int	ucango(t_mlx *root, int x, int y)
{
	if (is_wall(root, x, y))
		return (0);
	compteur_de_pas();
	return (1);
}

int	moove_player(int keycode, t_mlx *root)
{
	if (keycode == 65307)
		mlx_loop_end(root->mlx);

	if ((keycode == RIGHT || keycode == RIGHTA)
		&& ucango(root, root->player->x + TILE_SIZE, root->player->y))
		root->player->x += TILE_SIZE;
	if ((keycode == LEFT || keycode == LEFTA)
		&& ucango(root, root->player->x - TILE_SIZE, root->player->y))
		root->player->x -= TILE_SIZE;
	if ((keycode == UP || keycode == UPA)
		&& ucango(root, root->player->x, root->player->y - TILE_SIZE))
		root->player->y -= TILE_SIZE;
	if ((keycode == DOWN || keycode == DOWNA)
		&& ucango(root, root->player->x, root->player->y + TILE_SIZE))
		root->player->y += TILE_SIZE;
	if (!root->player->img)
		invalid_map_error(root, NULL);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->player->img,
		root->player->x, root->player->y);
	return (0);
}
