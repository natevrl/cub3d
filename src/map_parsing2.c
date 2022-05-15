/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:55:52 by mderome           #+#    #+#             */
/*   Updated: 2022/05/15 15:06:53 by mderome          ###   ########.fr       */
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
	while (i < root->y)
	{
		j = 0;
		while (root->map1[i][j] && j < root->x)
		{
			if (root->map1[i][j] && root->map1[i][j] == '0')
				root->map[i][j] = 2;
			else if (root->map1[i][j] && root->map1[i][j] == '1')
				root->map[i][j] = 1;
			else if (root->map1[i][j] == 'S' || root->map1[i][j] == 'E'
				|| root->map1[i][j] == 'W' || root->map1[i][j] == 'N')
			{
				root->pos_p_x = j;
				root->pos_p_y = i;
				root->map[i][j] = 2;
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
		root->map[index][i] = 3;
		i++;
	}
}

void	map_parsing2(t_mlx *root)
{
	int	i;

	root->x = find_bigger_len(root->map1);
	root->y = tab_len(root->map1);
	root->map = (int **)malloc(sizeof(int *) * (root->y + 2));
	i = 0;
	while (i < root->y)
	{
		root->map[i] = malloc(sizeof(int) * (root->x + 2));
		set_all_at_3(root, i);
		i++;
	}
	set_space_and_1(root);
	if (flood_fill(root, root->pos_p_y, root->pos_p_x, 0))
		invalid_map_error(root, NULL);
}
