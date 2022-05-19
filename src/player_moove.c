
#include "../header.h"


void move_player(t_mlx *root)
{
	float move_step;
	float new_x;
	float new_y;
	
	move_step = root->player->pas_chasse * root->player->walk_speed;
	new_x = root->player->x - sin(root->player->rota_angle) * move_step;
	new_y = root->player->y + cos(root->player->rota_angle) * move_step;
	if (root->player->pas_chasse == 0)
	{
		root->player->rota_angle += root->player->turn_direction * root->player->turn_speed;
		move_step = root->player->walk_direction * root->player->walk_speed;
		new_x = root->player->x + cos(root->player->rota_angle) * move_step;
		new_y = root->player->y + sin(root->player->rota_angle) * move_step;
	}
	if (!there_is_wall(root, new_x, new_y))
	{
		root->player->x = new_x;
		root->player->y = new_y;
	}
}

int	press_actions(int keycode, t_mlx *root)
{
	if (keycode == 65307)
		mlx_loop_end(root->mlx);

	if (keycode == RIGHTA)
		root->player->turn_direction += 1;
	if (keycode == LEFTA)
		root->player->turn_direction -= 1;
	if (keycode == RIGHT)
		root->player->pas_chasse += 1;
	if (keycode == LEFT)
		root->player->pas_chasse -= 1;
	if ((keycode == UP || keycode == UPA))
		root->player->walk_direction += 1;
	if ((keycode == DOWN || keycode == DOWNA))
		root->player->walk_direction -= 1;
	return (0);
}

int	release_actions(int keycode, t_mlx *root)
{
	if (keycode == 65307)
		mlx_loop_end(root->mlx);
	if (keycode == RIGHTA)
		root->player->turn_direction = 0;
	if (keycode == LEFTA)
		root->player->turn_direction = 0;
	if (keycode == RIGHT)
		root->player->pas_chasse = 0;
	if (keycode == LEFT)
		root->player->pas_chasse = 0;
	if ((keycode == UP || keycode == UPA))
		root->player->walk_direction = 0;
	if ((keycode == DOWN || keycode == DOWNA))
		root->player->walk_direction = 0;
	return (0);
}