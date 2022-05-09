/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_put_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:40:45 by v3r               #+#    #+#             */
/*   Updated: 2022/05/09 20:57:05 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"




// int	put_wall(t_mlx *root, int x, int y)
// {
// 	static int	f = -1;

// 	root->walls->x[++f] = x;
// 	root->walls->y[f] = y;
// 	root->maps->r_path = "./images/rock.xpm";
// 	root->maps->img = mlx_xpm_file_to_image(root->mlx, root->maps->r_path,
// 			&root->maps->width, &root->maps->height);
// 	if (!root->maps->img)
// 		return (0);
// 	mlx_put_image_to_window(root->mlx, root->mlx_win, root->maps->img, x, y);
// 	mlx_destroy_image(root->mlx, root->maps->img);
// 	return (1);
// }


// // int put_line(t_mlx *root)
// // {
	
// // }

// int	put_player(t_mlx *root, int x, int y)
// {
// 	printf("%d\n", x);
// 	printf("%d\n", y);
// 	root->player->x = x;
// 	root->player->y = y;
// 	my_mlx_pixel_put(root, x, y, 0x00FF0000);

// 	// root->player->r_path = "./images/character.xpm";
// 	// root->player->img = mlx_xpm_file_to_image(root->mlx, root->player->r_path,
// 	// 		&root->player->width, &root->player->height);
// 	// if (!root->player->img)
// 	// 	return (0);
// 	mlx_put_image_to_window(root->mlx, root->mlx_win, root->player->img, x, y);
// 	return (1);
// }
