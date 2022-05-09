/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:41:47 by v3r               #+#    #+#             */
/*   Updated: 2022/05/09 16:42:33 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	ucango(t_mlx *vars, int x, int y)
{
	if (vars->enemies->touched == 1)
		return (0);
	if (is_wall(vars, x, y))
		return (0);
	if (is_enemies(vars, x, y))
		return (0);
	if (is_escape(vars, x, y))
		return (0);
	is_collectible(vars, x, y);
	compteur_de_pas();
	return (1);
}

int	moove_player(int keycode, t_mlx *vars)
{
	if (keycode == 65307)
		mlx_loop_end(vars->mlx);
	if (vars->enemies->touched == 0)
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->maps->img,
			vars->player->x, vars->player->y);
	if ((keycode == RIGHT || keycode == RIGHTA)
		&& ucango(vars, vars->player->x + IMG_BITS, vars->player->y))
		vars->player->x += IMG_BITS;
	if ((keycode == LEFT || keycode == LEFTA)
		&& ucango(vars, vars->player->x - IMG_BITS, vars->player->y))
		vars->player->x -= IMG_BITS;
	if ((keycode == UP || keycode == UPA)
		&& ucango(vars, vars->player->x, vars->player->y - IMG_BITS))
		vars->player->y -= IMG_BITS;
	if ((keycode == DOWN || keycode == DOWNA)
		&& ucango(vars, vars->player->x, vars->player->y + IMG_BITS))
		vars->player->y += IMG_BITS;
	if (!vars->player->img)
		invalid_map_error(vars, NULL);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player->img,
		vars->player->x, vars->player->y);
	return (0);
}
