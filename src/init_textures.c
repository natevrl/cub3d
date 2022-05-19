#include "../header.h"


void	setup_one_texture(t_mlx *root, char *path, void **direction)
{
	int txtsize;

	txtsize = 64;
	*direction = mlx_xpm_file_to_image(root->mlx, path, &txtsize, &txtsize);
	if (!direction)
		kill_all(root);
}

char	*take_path(char *data)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (data[i] != ' ')
		i++;
	while (data[i] == ' ')
		i++;
	ret = malloc(sizeof(char) * (ft_strlen(data) - i));
	j = 0;
	while (data[i] != '\n')
	{
		ret[j] = data[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

void	setup_textures(t_mlx *root)
{
	int	i;

	i = 0;
	while (root->data_map[i])
	{
		if (ft_strncmp(root->data_map[i], "NO ", 3) == 0)
			root->no = take_path(root->data_map[i]);
		if (ft_strncmp(root->data_map[i], "SO ", 3) == 0)
			root->so = take_path(root->data_map[i]);
		if (ft_strncmp(root->data_map[i], "EA ", 3) == 0)
			root->ea = take_path(root->data_map[i]);
		if (ft_strncmp(root->data_map[i], "WE ", 3) == 0)
			root->we = take_path(root->data_map[i]);
		i++;
	}
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