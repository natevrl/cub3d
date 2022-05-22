/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:03:39 by v3r               #+#    #+#             */
/*   Updated: 2022/05/22 16:00:19 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

float	normalize_ray(float angle)
{
	angle = remainder(angle, DOUBLE_PI);
	if (angle < 0)
	{
		angle = DOUBLE_PI + angle;
	}
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	init_ray_pos(t_direction *pos, float ray_angle)
{
	pos->found_wall = FALSE;
	pos->wall_content = 0;
	pos->wall_hit_x = 0;
	pos->wall_hit_y = 0;
	pos->facing_down = (ray_angle > 0 && ray_angle < PI);
	pos->facing_up = !pos->facing_down;
	pos->facing_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
	pos->facing_left = !pos->facing_right;
}

void	calcul_hit_distance(t_mlx *root, t_direction *horz, t_direction *vert)
{
	if (horz->found_wall)
		horz->hit_distance = distance_between_points(root->player->x,
				root->player->y, horz->wall_hit_x, horz->wall_hit_y);
	else
		horz->hit_distance = FLT_MAX;
	if (vert->found_wall)
		vert->hit_distance = distance_between_points(root->player->x,
				root->player->y, vert->wall_hit_x, vert->wall_hit_y);
	else
		vert->hit_distance = FLT_MAX;
}

void	find_smallest_hit_distance(t_rays *rays, t_direction *horz,
	t_direction *vert)
{
	rays->distance = horz->hit_distance;
	rays->wall_hit_x = horz->wall_hit_x;
	rays->wall_hit_y = horz->wall_hit_y;
	rays->wall_hit_content = horz->wall_content;
	rays->was_hit_vertical = FALSE;
	if (vert->hit_distance < horz->hit_distance)
	{
		rays->distance = vert->hit_distance;
		rays->wall_hit_x = vert->wall_hit_x;
		rays->wall_hit_y = vert->wall_hit_y;
		rays->wall_hit_content = vert->wall_content;
		rays->was_hit_vertical = TRUE;
	}
}
