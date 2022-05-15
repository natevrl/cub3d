/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v3r <v3r@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:41:09 by v3r               #+#    #+#             */
/*   Updated: 2022/05/15 20:44:41 by v3r              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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