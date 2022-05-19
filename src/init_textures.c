#include "../header.h"


void	setup_one_texture(t_mlx *root, char *path, void **direction)
{
	int txtsize;

	txtsize = 64;
	*direction = mlx_xpm_file_to_image(root->mlx, path, &txtsize, &txtsize);
	if (!direction)
		kill_all(root);
}

void	setup_textures(t_mlx *root)
{
	root->no = "textures/txt1.xpm";
	root->so = "textures/mur64.xpm";
	root->we = "textures/wall_wood.xpm";
	root->ea = "textures/txt1.xpm";
	setup_one_texture(root, root->we, &root->texture_left);
	setup_one_texture(root, root->ea, &root->texture_right);
	setup_one_texture(root, root->no, &root->texture_down);
	setup_one_texture(root, root->so, &root->texture_up);
}

void	init_texture(t_mlx *root, t_img **texture)
{
	(*texture)->data_color_addr[0] = (int *)mlx_get_data_addr(root->texture_down,
			&(*texture)->bits_per_pixel, &(*texture)->line_length, &(*texture)->endian);
	(*texture)->data_color_addr[1] = (int *)mlx_get_data_addr(root->texture_up,
			&(*texture)->bits_per_pixel, &(*texture)->line_length, &(*texture)->endian);
	(*texture)->data_color_addr[2] = (int *)mlx_get_data_addr(root->texture_left,
			&(*texture)->bits_per_pixel, &(*texture)->line_length, &(*texture)->endian);
	(*texture)->data_color_addr[3] = (int *)mlx_get_data_addr(root->texture_right,
			&(*texture)->bits_per_pixel, &(*texture)->line_length, &(*texture)->endian);
}