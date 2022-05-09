#include "../header.h"

static void	kill_window(t_mlx *vars)
{
	if (vars->mlx)
	{
		if (vars->player->img)
			mlx_destroy_image(vars->mlx, vars->player->img);
		if (vars->maps->img)
			mlx_destroy_image(vars->mlx, vars->maps->img);
		if (vars->mlx_win)
			mlx_destroy_window(vars->mlx, vars->mlx_win);
		mlx_destroy_display(vars->mlx);
	}
}

static void	kill_enemies(t_mlx *vars)
{
	if (vars->enemies->y)
		free(vars->enemies->y);
	if (vars->enemies->x)
		free(vars->enemies->x);
	if (vars->enemies)
		free(vars->enemies);
}

void	kill_all(t_mlx *vars)
{
	kill_window(vars);
	if (vars->player)
		free(vars->player);
	if (vars->maps)
		free(vars->maps);
	if (vars->walls->y)
		free(vars->walls->y);
	if (vars->walls->x)
		free(vars->walls->x);
	if (vars->walls)
		free(vars->walls);
	if (vars->collectible->y)
		free(vars->collectible->y);
	if (vars->collectible->x)
		free(vars->collectible->x);
	if (vars->collectible)
		free(vars->collectible);
	kill_enemies(vars);
	if (vars->mlx)
		free(vars->mlx);
	if (vars)
		free(vars);
	exit(0);
}