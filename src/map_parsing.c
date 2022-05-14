/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v3r <v3r@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:41:09 by v3r               #+#    #+#             */
/*   Updated: 2022/05/14 19:04:03 by v3r              ###   ########.fr       */
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

void	map_parsing(t_mlx *root)
{
	char	buffer[BUFF_SIZE];
	char	*all_maps;
	int		ret;
	int		fd;

	fd = open(root->path, O_RDONLY);
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

// void	map_drawer(t_mlx *root)
// {
// 	int		fd;
// 	char	*gnl;
// 	int		line;
// 	int		error;


// 	char	**map;
// 	int		fd;
// 	int		i;
// 	int		size;

// 	i = 0;
// 	size = ft_get_size(file);
// 	map = ft_malloc(sizeof(char *) * size + 1);
	

// 	fd = open(root->path, O_RDONLY);
// 	check_open_error(root, fd);
// 	line = 0;
// 	error = 0;
// 	while (1)
// 	{
// 		 = get_next_line(fd);
// 		if (!gnl)
// 			break ;
// 		if (line_bad_len(root, gnl) || walls_error(root, ++line, gnl))
// 			error++;
// 		else
// 			free(gnl);
// 	}
// 	if (error > 0)
// 		invalid_map_error(root, 0);
// 	close(fd);
// }

char	**fill_map(t_mlx *root)
{
	int		fd;
	int		i;
	char	**maps;

	fd = open(root->path, O_RDONLY);
	maps = malloc(sizeof(char *) * NUMBER_MAP_ROWS);
	i = -1;
	while (++i < NUMBER_MAP_ROWS)
		maps[i] = get_next_line(fd);
	close(fd);
	return (maps);
}