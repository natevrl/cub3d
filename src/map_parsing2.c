/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:55:52 by mderome           #+#    #+#             */
/*   Updated: 2022/05/18 14:37:39 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	find_bigger_len(char **map)
{
	int		i;
	size_t	ret;
	size_t	tmp;

	i = 0;
	ret = ft_strlen(map[i]);
	while (map && map[i])
	{
		tmp = ft_strlen(map[i]);
		if (tmp > ret)
			ret = tmp;
		i++;
	}
	return ((int)ret);
}

static void	set_space_and_1(t_mlx *root)
{
	int	i;
	int	j;

	i = 0;
	while (i < root->y && root->map)
	{
		j = 0;
		while (root->map[i][j] && j < root->x )
		{
			if (root->map[i][j] == '\0')
				break ;
			if (root->map[i][j] && root->map[i][j] == '0')
				root->map_int[i][j] = 2;
			else if (root->map[i][j] && root->map[i][j] == '1')
				root->map_int[i][j] = 1;
			else if (root->map[i][j] == 'S' || root->map[i][j] == 'E'
				|| root->map[i][j] == 'W' || root->map[i][j] == 'N')
			{
				root->player->x = j;
				root->player->y = i;
				root->map_int[i][j] = 2;
				root->player->orientation = root->map_int[i][j];
			}
			j++;
		}
		i++;
	}
}

static void	set_all_at_3(t_mlx *root, int index)
{
	int	i;

	i = 0;
	while (i < root->x)
	{
		root->map_int[index][i] = 3;
		i++;
	}
}

void	map_parsing2(t_mlx *root)
{
	int	i;

	root->x = find_bigger_len(root->map);
	root->y = tab_len(root->map);
	root->map_int = (int **)malloc(sizeof(int *) * (root->y));
	i = 0;
	while (i < root->y)
	{
		root->map_int[i] = malloc(sizeof(int) * (root->x));
		set_all_at_3(root, i);
		i++;
	}
	set_space_and_1(root);
	if (flood_fill(root, root->player->y, root->player->x, 0))
		invalid_map_error(root, NULL);
	root->player->x = root->player->x * TILE_SIZE;
	root->player->y = root->player->y * TILE_SIZE;
}