/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:32:57 by mderome           #+#    #+#             */
/*   Updated: 2022/05/23 13:31:36 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	there_is_wall(t_mlx *root, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if ((x < 0 || x >= (TILE_SIZE * root->x)) || (y < 0
			|| y >= (TILE_SIZE * root->y)))
		return (TRUE);
	if (root->map[map_y][map_x] != 0 && root->map[map_y][map_x] != '1')
		return (FALSE);
	return (TRUE);
}

void	init_struct(t_mlx *root, char *path)
{
	root->path = path;
	root->map = NULL;
	root->data_map = NULL;
	root->is_player = 0;
	root->mlx = 0;
	root->mlx_win = NULL;
	root->text_up = NULL;
	root->text_down = NULL;
	root->text_left = NULL;
	root->text_right = NULL;
	root->ea = NULL;
	root->we = NULL;
	root->so = NULL;
	root->no = NULL;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

int	init_player(t_mlx *root, int x, int y)
{
	t_img	*player;

	player = malloc(sizeof(t_img));
	player->x = x;
	player->y = y;
	player->height = 1;
	player->width = 1;
	root->pos_p_x = 0;
	root->pos_p_y = 0;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->pas_chasse = 0;
	player->rota_angle = 0;
	player->walk_speed = 4;
	player->turn_speed = 4 * (PI / 180);
	root->player = player;
	return (1);
}

int	update_image(t_mlx *root)
{
	raycast(root);
	generate_3d_projection(root);
	move_player(root);
	free(root->rays);
	root->rays = NULL;
	return (1);
}
