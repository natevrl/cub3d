/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:41:09 by v3r               #+#    #+#             */
/*   Updated: 2022/05/11 13:07:50 by mderome          ###   ########.fr       */
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

void	print_tab(char **tab)
{
	int	i = 0;

	while (tab && tab[i])
	{
		printf("%s", tab[i]);
		i++;
	}
}

void	map_parsing(t_mlx *root, char *str)
{
	char	*buffer;
	char	*all_maps;
	int		fd;

	fd = open(str, O_RDONLY);
	check_open_error(root, fd);
	all_maps = take_data(root, fd);
	buffer = get_next_line(fd);
	while (buffer != NULL)
	{
		all_maps = ftstrjoin(all_maps, buffer);
		buffer = get_next_line(fd);
	}
	count_elements(root, all_maps);
	print_tab(root->data_map);
	printf("%s", all_maps);
	free(all_maps);
	close(fd);
}
