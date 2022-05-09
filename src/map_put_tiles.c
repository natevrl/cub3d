/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_put_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:40:45 by v3r               #+#    #+#             */
/*   Updated: 2022/05/09 16:42:33 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	put_wall(t_mlx *vars, int x, int y)
{
	static int	f = -1;

	vars->walls->x[++f] = x;
	vars->walls->y[f] = y;
	vars->maps->r_path = "./images/rock.xpm";
	vars->maps->img = mlx_xpm_file_to_image(vars->mlx, vars->maps->r_path,
			&vars->maps->img_width, &vars->maps->img_height);
	if (!vars->maps->img)
		return (0);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->maps->img, x, y);
	mlx_destroy_image(vars->mlx, vars->maps->img);
	return (1);
}

int	put_ground(t_mlx *vars, int x, int y)
{
	vars->maps->r_path = "./images/center.xpm";
	vars->maps->img = mlx_xpm_file_to_image(vars->mlx, vars->maps->r_path,
			&vars->maps->img_width, &vars->maps->img_height);
	if (!vars->maps->img)
		return (0);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->maps->img, x, y);
	mlx_destroy_image(vars->mlx, vars->maps->img);
	return (1);
}

int	put_player(t_mlx *vars, int x, int y)
{
	vars->player->x = x;
	vars->player->y = y;
	vars->player->r_path = "./images/character.xpm";
	vars->player->img = mlx_xpm_file_to_image(vars->mlx, vars->player->r_path,
			&vars->player->img_width, &vars->player->img_height);
	if (!vars->player->img)
		return (0);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player->img, x, y);
	return (1);
}


// int	put_collectible(t_mlx *vars, int x, int y)
// {
// 	static int	k = -1;

// 	vars->collectible->x[++k] = x;
// 	vars->collectible->y[k] = y;
// 	vars->maps->r_path = "./images/collectible.xpm";
// 	vars->maps->img = mlx_xpm_file_to_image(vars->mlx, vars->maps->r_path,
// 			&vars->maps->img_width, &vars->maps->img_height);
// 	if (!vars->maps->img)
// 		return (0);
// 	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->maps->img, x, y);
// 	mlx_destroy_image(vars->mlx, vars->maps->img);
// 	return (1);
// }


// int	put_escape(t_mlx *vars, int x, int y)
// {
// 	vars->walls->x[0] = x;
// 	vars->walls->y[0] = y;
// 	vars->maps->r_path = "./images/escape.xpm";
// 	vars->maps->img = mlx_xpm_file_to_image(vars->mlx, vars->maps->r_path,
// 			&vars->maps->img_width, &vars->maps->img_height);
// 	if (!vars->maps->img)
// 		return (0);
// 	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->maps->img, x, y);
// 	mlx_destroy_image(vars->mlx, vars->maps->img);
// 	return (1);
// }
