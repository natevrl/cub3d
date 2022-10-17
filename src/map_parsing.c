/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:41:09 by v3r               #+#    #+#             */
/*   Updated: 2022/06/07 15:34:13 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	count_elements(t_mlx *root, char *buffer)
{
	int	i;
	int	j;

	i = -1;
	root->map = ft_split(buffer, '\n');
	while (root->map[++i])
	{
		j = 0;
		while (root->map[i][j])
		{
			if (root->map[i][j] == 'N' || root->map[i][j] == 'S'
				|| root->map[i][j] == 'E' || root->map[i][j] == 'W')
			{
				root->pos_p_x = i;
				root->pos_p_y = j;
				root->is_player++;
			}
			j++;
		}
	}
	if (root->is_player != 1)
		invalid_map_error(root, buffer);
}

static void	up_data(t_mlx *root, char *line)
{
	char	**new_data;
	int		i;

	new_data = (char **)malloc(sizeof(char *) * (tab_len(root->data_map) + 2));
	i = 0;
	while (root->data_map && root->data_map[i])
	{
		new_data[i] = ft_strdup(root->data_map[i]);
		i++;
	}
	new_data[i] = ft_strdup(line);
	new_data[i + 1] = NULL;
	free_tab(root->data_map);
	root->data_map = new_data;
}

static int	check_start_map(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (1);
	return (0);
}

static char	*take_data(t_mlx *root, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (check_start_map(line) != 1 && line)
	{
		if (line[0] != '\n')
			up_data(root, line);
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	map_parsing(t_mlx *root, char *str)
{
	char	*buffer;
	char	*all_maps;
	int		fd;
	int		error;

	error = 0;
	fd = open(str, O_RDONLY | O_RDWR);
	if (fd < 0)
		check_open_error(root, fd);
	check_open_error(root, fd);
	all_maps = take_data(root, fd);
	buffer = get_next_line(fd);
	while (buffer != NULL)
	{
		all_maps = ftstrjoin(all_maps, buffer);
		free(buffer);
		buffer = get_next_line(fd);
		if (buffer && buffer[0] == '\n')
			error = 1;
	}
	all_maps = ftstrjoin(all_maps, buffer);
	return_map_parsing(root, all_maps, fd);
	if (error == 1)
		invalid_map_error(root, NULL);
	check_data_map(root);
}
