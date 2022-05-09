/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_put_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:40:45 by v3r               #+#    #+#             */
/*   Updated: 2022/05/09 18:11:54 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	put_wall(t_mlx *root, int x, int y)
{
	static int	f = -1;

	root->walls->x[++f] = x;
	root->walls->y[f] = y;
	root->maps->r_path = "./images/rock.xpm";
	root->maps->img = mlx_xpm_file_to_image(root->mlx, root->maps->r_path,
			&root->maps->img_width, &root->maps->img_height);
	if (!root->maps->img)
		return (0);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->maps->img, x, y);
	mlx_destroy_image(root->mlx, root->maps->img);
	return (1);
}

int	put_ground(t_mlx *root, int x, int y)
{
	root->maps->r_path = "./images/center.xpm";
	root->maps->img = mlx_xpm_file_to_image(root->mlx, root->maps->r_path,
			&root->maps->img_width, &root->maps->img_height);
	if (!root->maps->img)
		return (0);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->maps->img, x, y);
	mlx_destroy_image(root->mlx, root->maps->img);
	return (1);
}

int	put_player(t_mlx *root, int x, int y)
{
	root->player->x = x;
	root->player->y = y;
	root->player->r_path = "./images/character.xpm";
	root->player->img = mlx_xpm_file_to_image(root->mlx, root->player->r_path,
			&root->player->img_width, &root->player->img_height);
	if (!root->player->img)
		return (0);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->player->img, x, y);
	return (1);
}


// int	put_collectible(t_mlx *root, int x, int y)
// {
// 	static int	k = -1;

// 	root->collectible->x[++k] = x;
// 	root->collectible->y[k] = y;
// 	root->maps->r_path = "./images/collectible.xpm";
// 	root->maps->img = mlx_xpm_file_to_image(root->mlx, root->maps->r_path,
// 			&root->maps->img_width, &root->maps->img_height);
// 	if (!root->maps->img)
// 		return (0);
// 	mlx_put_image_to_window(root->mlx, root->mlx_win, root->maps->img, x, y);
// 	mlx_destroy_image(root->mlx, root->maps->img);
// 	return (1);
// }


// int	put_escape(t_mlx *root, int x, int y)
// {
// 	root->walls->x[0] = x;
// 	root->walls->y[0] = y;
// 	root->maps->r_path = "./images/escape.xpm";
// 	root->maps->img = mlx_xpm_file_to_image(root->mlx, root->maps->r_path,
// 			&root->maps->img_width, &root->maps->img_height);
// 	if (!root->maps->img)
// 		return (0);
// 	mlx_put_image_to_window(root->mlx, root->mlx_win, root->maps->img, x, y);
// 	mlx_destroy_image(root->mlx, root->maps->img);
// 	return (1);
// }
