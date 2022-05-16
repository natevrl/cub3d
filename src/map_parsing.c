/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:41:09 by v3r               #+#    #+#             */
/*   Updated: 2022/05/16 18:57:35 by nbenhado         ###   ########.fr       */
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
	{
		maps[i] = get_next_line(fd);
	}
	close(fd);
	return (maps);
}