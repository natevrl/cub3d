/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:41:09 by v3r               #+#    #+#             */
/*   Updated: 2022/05/09 18:38:24 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// calcule la resolution de la map et le nombre de walls & collectibles
// check si la map contient le bon nombre d'elements
static void	count_elements(t_mlx *root, char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '1')
			root->walls->max++;
		else if (buffer[i] == 'P')
			root->is_player++;
		else if (buffer[i] != '\n' && buffer[i] != '0')
			invalid_map_error(root, buffer);
		if (buffer[i] == '\n' || buffer[i + 1] == '\0')
			root->win_height++;
		i++;
	}
	if (root->is_player != 1)
		invalid_map_error(root, buffer);
	root->win_width = ((i + 1) - root->win_height) / root->win_height;
}

void	map_parsing(t_mlx *root, char *str)
{
	char	buffer[BUFF_SIZE];
	char	*all_maps;
	int		ret;
	int		fd;

	fd = open(str, O_RDONLY);
	check_open_error(root, fd);
	ret = 1;
	all_maps = 0;
	while (ret > 0)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		check_read_error(root, ret, all_maps);
		buffer[ret] = '\0';
		all_maps = ftstrjoin(all_maps, buffer);
	}
	count_elements(root, all_maps);
	free(all_maps);
	close(fd);
}
