/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:55:57 by mderome           #+#    #+#             */
/*   Updated: 2022/06/07 15:35:41 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	setup_one_texture(t_mlx *root, char *path, void **direction)
{
	int	txtsize;
	int	txtsize2;

	txtsize = 64;
	*direction = mlx_xpm_file_to_image(root->mlx, path, &txtsize, &txtsize2);
	if (txtsize != 64 || txtsize2 != 64)
	{
		printf("Wrong size image\n");
		kill_all(root);
	}
	if (!(*direction))
		data_error(root);
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
		else if (ft_strncmp(root->data_map[i], "SO ", 3) == 0)
			root->so = take_path(root->data_map[i]);
		else if (ft_strncmp(root->data_map[i], "EA ", 3) == 0)
			root->ea = take_path(root->data_map[i]);
		else if (ft_strncmp(root->data_map[i], "WE ", 3) == 0)
			root->we = take_path(root->data_map[i]);
		i++;
	}
	setup_one_texture(root, root->no, &root->text_left);
	setup_one_texture(root, root->ea, &root->text_down);
	setup_one_texture(root, root->we, &root->text_up);
	setup_one_texture(root, root->so, &root->text_right);
}

void	init_texture(t_mlx *root, t_img **texture)
{
	(*texture)->data_color_addr[0] = (int *)mlx_get_data_addr(root->text_down,
			&(*texture)->bits_per_pixel,
			&(*texture)->line_length, &(*texture)->endian);
	(*texture)->data_color_addr[1] = (int *)mlx_get_data_addr(root->text_up,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
	(*texture)->data_color_addr[2] = (int *)mlx_get_data_addr(root->text_left,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
	(*texture)->data_color_addr[3] = (int *)mlx_get_data_addr(root->text_right,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
}
