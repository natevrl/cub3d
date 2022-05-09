/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:41:09 by v3r               #+#    #+#             */
/*   Updated: 2022/05/09 16:42:33 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// calcule la resolution de la map et le nombre de walls & collectibles
// check si la map contient le bon nombre d'elements
static void	count_elements(t_mlx *vars, char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '1')
			vars->walls->max++;
		else if (buffer[i] == 'P')
			vars->is_player++;
		else if (buffer[i] != '\n' && buffer[i] != '0')
			invalid_map_error(vars, buffer);
		if (buffer[i] == '\n' || buffer[i + 1] == '\0')
			vars->win_height++;
		i++;
	}
	if (vars->is_player != 1)
		invalid_map_error(vars, buffer);
	vars->win_width = ((i + 1) - vars->win_height) / vars->win_height;
}

void	map_parsing(t_mlx *vars, char *str)
{
	char	buffer[BUFF_SIZE];
	char	*all_maps;
	int		ret;
	int		fd;

	fd = open(str, O_RDONLY);
	check_open_error(vars, fd);
	ret = 1;
	all_maps = 0;
	while (ret > 0)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		check_read_error(vars, ret, all_maps);
		buffer[ret] = '\0';
		all_maps = ftstrjoin(all_maps, buffer);
	}
	count_elements(vars, all_maps);
	free(all_maps);
	close(fd);
}
