/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:39:18 by v3r               #+#    #+#             */
/*   Updated: 2022/05/24 14:04:59 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// setup les bons pixel de couleurs selon les textures de chaque murs
// texture.data_color_addr[i][] ==
// --> trouve le bon pixel de couleur stocker en memoire
void	setup_colors(t_mlx *root, t_img *img, int y, int x)
{
	int	i;
	int	dist_from_top;
	int	texture_color_pixel[4];

	dist_from_top = y + (root->project->wallstrip_h / 2) - (WINDOW_HEIGHT / 2);
	root->texture->txt_offset_y = dist_from_top * \
								((float)TILE_SIZE / root->project->wallstrip_h);
	i = -1;
	while (++i != 4)
		texture_color_pixel[i] = root->texture->data_color_addr[i][(TILE_SIZE
				* root->texture->txt_offset_y) + root->texture->txt_offset_x];
	if (root->rays[x].was_hit_vertical && root->rays[x].is_ray_facing_right)
		my_mlx_pixel_put(img, x, y, texture_color_pixel[0]);
	else if (root->rays[x].was_hit_vertical && root->rays[x].is_ray_facing_left)
		my_mlx_pixel_put(img, x, y, texture_color_pixel[1]);
	else if (root->rays[x].is_ray_facing_up)
		my_mlx_pixel_put(img, x, y, texture_color_pixel[2]);
	else
		my_mlx_pixel_put(img, x, y, texture_color_pixel[3]);
}

// rempli la map des couleurs recuperer pour le sol, plafond et textures
// (int)root->rays[i].wall_hit_y % TILE_SIZE; == 
// ---> trouver la bonne colonne de pixel au sein d'une texture
void	render_colors(t_mlx *root, t_img *img, t_project3d *project, int i)
{
	int		y;

	root->texture = malloc(sizeof(t_img));
	init_texture(root, &root->texture);
	y = project->wall_bot_pix;
	while (++y <= WINDOW_HEIGHT)
		my_mlx_pixel_put(img, i, y, root->floor);
	y = project->wall_top_pix;
	if (root->rays[i].was_hit_vertical)
		root->texture->txt_offset_x = (int)root->rays[i].wall_hit_y % TILE_SIZE;
	else
		root->texture->txt_offset_x = (int)root->rays[i].wall_hit_x % TILE_SIZE;
	while (++y <= project->wall_bot_pix)
		setup_colors(root, img, y, i);
	y = 0;
	while (++y <= project->wall_top_pix)
		my_mlx_pixel_put(img, i, y, root->ceiling);
	free(root->texture);
}

// calcul la distance entre le player et la texture
// trouve la taille de la texture
void	projections(t_mlx *root, t_project3d **project, int i)
{
	(*project)->perp_distance = root->rays[i].distance * \
				cos(root->rays[i].ray_angle - root->player->rota_angle);
	(*project)->projected_wall_h = (TILE_SIZE / (*project)->perp_distance) * \
						((WINDOW_WIDTH / 2) / tan((120 * (M_PI / 180)) / 2));
	(*project)->wallstrip_h = (int)(*project)->projected_wall_h;
	(*project)->wall_top_pix = (WINDOW_HEIGHT / 2) - \
											((*project)->wallstrip_h / 2);
	if ((*project)->wall_top_pix < 0)
		(*project)->wall_top_pix = 0;
	(*project)->wall_bot_pix = (WINDOW_HEIGHT / 2) + \
											((*project)->wallstrip_h / 2);
	if ((*project)->wall_bot_pix > WINDOW_HEIGHT)
		(*project)->wall_bot_pix = WINDOW_HEIGHT;
}

// projete toute les rays a la bonne taille + place les pixel de couleurs
void	generate_3d_projection(t_mlx *root)
{
	int			i;
	t_img		img;

	root->project = malloc(sizeof(t_img));
	img.img = mlx_new_image(root->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
									&img.line_length, &img.endian);
	i = -1;
	while (++i < NUMBER_OF_RAYS)
	{
		projections(root, &root->project, i);
		render_colors(root, &img, root->project, i);
	}
	mlx_put_image_to_window(root->mlx, root->mlx_win, img.img, 0, 0);
	mlx_destroy_image(root->mlx, img.img);
	free(root->project);
	root->project = NULL;
}
