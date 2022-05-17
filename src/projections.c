#include "../header.h"


// setup les bons pixel de couleurs selon les textures de chaque murs
// texture.data_color_addr[i][(TILE_SIZE * texture.texture_offset_y) + texture.texture_offset_x] ==
//	-- > permet daller chercher pile le bon pixel dans les datas de la texture en memoire
void	setup_colors(t_mlx *root, t_project3d project, t_img texture, t_img *img, int y, int x)
{
	int	i;
	int	distance_from_top;
	int texture_color_pixel[4];
	(void)root;
	distance_from_top = y + (project.wall_strip_h / 2) - (WINDOW_HEIGHT / 2);
	texture.texture_offset_y = distance_from_top * ((float)TILE_SIZE / project.wall_strip_h);
	i = -1;
	while (++i != 4)
		texture_color_pixel[i] = texture.data_color_addr[i][(TILE_SIZE * texture.texture_offset_y) + texture.texture_offset_x];
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
// (int)root->rays[i].wall_hit_y % TILE_SIZE; == trouver la bonne colonne de pixel au sein d'une texture
void	render_colors(t_mlx *root, t_img *img, t_project3d project, int i)
{
	int			y;
	t_img		texture;

	init_texture(root, &texture);
	y = project.wall_bot_pix;
	while (++y <= (root->y * TILE_SIZE))
		my_mlx_pixel_put(img, i, y, root->floor);
	y = project.wall_top_pix;
	if (root->rays[i].was_hit_vertical)
		texture.texture_offset_x = (int)root->rays[i].wall_hit_y % TILE_SIZE;
	else
		texture.texture_offset_x = (int)root->rays[i].wall_hit_x % TILE_SIZE;
	// rempli la ray de haut en bas de la texture avec les bons pixel
	while (++y <= project.wall_bot_pix)
		setup_colors(root, project, texture, img, y, i);
	y = -1;
	while (++y <= project.wall_top_pix)
		my_mlx_pixel_put(img, i, y, root->ceiling);
}

// calcul la distance entre le player et la texture
// trouve la taille de la texture
void projections(t_mlx *root, t_project3d *project, int i)
{
	project->perp_distance = root->rays[i].distance * cos(root->rays[i].ray_angle - root->player->rotation_angle);
	project->projected_wall_h = (TILE_SIZE / project->perp_distance)
		* (((root->x * TILE_SIZE) / 2) / tan((120 * (PI / 180)) / 2));
	project->wall_strip_h = (int)project->projected_wall_h;
	project->wall_top_pix = ((root->y * TILE_SIZE) / 2) - (project->wall_strip_h / 2);
	if (project->wall_top_pix < 0)
		project->wall_top_pix = 0;
	project->wall_bot_pix = ((root->y * TILE_SIZE) / 2) + (project->wall_strip_h / 2);
	if (project->wall_bot_pix > (root->y * TILE_SIZE))
		project->wall_bot_pix = (root->y * TILE_SIZE);
}

// projete toute les rays a la bonne taille + place les pixel de couleurs
void	generate_3d_projection(t_mlx *root)
{
	int			i;
	t_img		img;
	t_project3d	project;

	img.img = mlx_new_image(root->mlx, (root->x * TILE_SIZE), (root->y * TILE_SIZE));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	i = -1;
	while (++i < NUMBER_OF_RAYS)
	{
		projections(root, &project, i);
		render_colors(root, &img, project, i);
	}
	mlx_put_image_to_window(root->mlx, root->mlx_win, img.img, 0, 0);
	mlx_destroy_image(root->mlx, img.img);
}