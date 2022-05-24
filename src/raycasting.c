/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:50:17 by v3r               #+#    #+#             */
/*   Updated: 2022/05/24 14:05:29 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Increment xstep and ystep until we find a wall
void	increment_until_wall(t_mlx *root, t_direction *pos, int flag)
{
	while ((pos->next_touch_x >= 0 && pos->next_touch_x <= root->x * TILE_SIZE)
		&& (pos->next_touch_y >= 0 && pos->next_touch_y <= root->y * TILE_SIZE))
	{
		pos->xtocheck = pos->next_touch_x;
		pos->ytocheck = pos->next_touch_y;
		if (flag == 1 && pos->facing_up)
			pos->ytocheck = pos->next_touch_y - 1;
		if (flag == 2 && pos->facing_left)
			pos->xtocheck = pos->next_touch_x - 1;
		if (there_is_wall(root, pos->xtocheck, pos->ytocheck))
		{
			pos->wall_hit_x = pos->next_touch_x;
			pos->wall_hit_y = pos->next_touch_y;
			protect_rays_error(root, pos);
			pos->wall_content = root->map[(int)floor(pos->ytocheck / TILE_SIZE)]
			[(int)floor(pos->xtocheck / TILE_SIZE)];
			pos->found_wall = TRUE;
			break ;
		}
		else
		{
			pos->next_touch_x += pos->xstep;
			pos->next_touch_y += pos->ystep;
		}
	}
}

// Find the y-coordinate of the closest horizontal grid intersection
// Find the x-coordinate of the closest horizontal grid intersection
// Calculate the increment xstep and ystep
void	calcul_horizontal_rays(t_mlx *root, t_direction *horz, float ray_angle)
{
	horz->yintercept = floor(root->player->y / TILE_SIZE) * TILE_SIZE;
	if (horz->facing_down)
		horz->yintercept += TILE_SIZE;
	horz->xintercept = root->player->x + (horz->yintercept - root->player->y) \
															/ tan(ray_angle);
	horz->ystep = TILE_SIZE;
	if (horz->facing_up)
		horz->ystep *= -1;
	horz->xstep = TILE_SIZE / tan(ray_angle);
	if (horz->facing_left && horz->xstep > 0)
		horz->xstep *= -1;
	if ((horz->facing_right && horz->xstep < 0))
		horz->xstep *= -1;
	horz->next_touch_x = horz->xintercept;
	horz->next_touch_y = horz->yintercept;
	increment_until_wall(root, horz, 1);
}

void	calcul_vertical_rays(t_mlx *root, t_direction *vert, float ray_angle)
{
	vert->xintercept = floor(root->player->x / TILE_SIZE) * TILE_SIZE;
	if (vert->facing_right)
		vert->xintercept += TILE_SIZE;
	vert->yintercept = root->player->y + (vert->xintercept - root->player->x) \
															* tan(ray_angle);
	vert->xstep = TILE_SIZE;
	if (vert->facing_left)
		vert->xstep *= -1;
	vert->ystep = TILE_SIZE * tan(ray_angle);
	if (vert->facing_up && vert->ystep > 0)
		vert->ystep *= -1;
	if (vert->facing_down && vert->ystep < 0)
		vert->ystep *= -1;
	vert->next_touch_x = vert->xintercept;
	vert->next_touch_y = vert->yintercept;
	increment_until_wall(root, vert, 2);
}

void	cast_one_ray(t_mlx *root, float ray_angle, t_rays *rays)
{
	t_direction	vert;
	t_direction	horz;

	ray_angle = normalize_ray(ray_angle);
	init_ray_pos(&horz, ray_angle);
	calcul_horizontal_rays(root, &horz, ray_angle);
	init_ray_pos(&vert, ray_angle);
	calcul_vertical_rays(root, &vert, ray_angle);
	calcul_hit_distance(root, &horz, &vert);
	find_smallest_hit_distance(rays, &horz, &vert);
	rays->ray_angle = ray_angle;
	rays->is_ray_facing_down = vert.facing_down;
	rays->is_ray_facing_up = vert.facing_up;
	rays->is_ray_facing_left = vert.facing_left;
	rays->is_ray_facing_right = vert.facing_right;
}

// ray_angle = root->player->rota_angle - (FOV_ANGLE / 2);
// ray_angle += FOV_ANGLE / NUMBER_OF_RAYS;
void	raycast(t_mlx *root)
{
	float	ray_angle;
	int		id;

	id = 0;
	ray_angle = root->player->rota_angle + atan((id - NUMBER_OF_RAYS / 2)
			/ ((WINDOW_WIDTH / 2) / tan((120 * (M_PI / 180)) / 2)));
	root->rays = malloc(sizeof(t_rays) * NUMBER_OF_RAYS + 1);
	while (id < NUMBER_OF_RAYS)
	{
		cast_one_ray(root, ray_angle, &root->rays[id]);
		ray_angle = root->player->rota_angle + atan((id - NUMBER_OF_RAYS / 2)
				/ ((WINDOW_WIDTH / 2) / tan((120 * (M_PI / 180)) / 2)));
		id++;
	}
}
