/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:33:44 by v3r               #+#    #+#             */
/*   Updated: 2022/05/24 14:03:17 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_map(t_mlx *root, char **map)
{
	int	i;
	int	j;

	i = 0;
	(void)root;
	while (map && map[i])
	{
		j = 0;
		while (map && map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(char **map)
{
	(void)map;
	return (0);
}
