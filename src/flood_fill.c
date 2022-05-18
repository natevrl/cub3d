/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:52:59 by mderome           #+#    #+#             */
/*   Updated: 2022/05/18 14:38:03 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_fail(t_mlx *root, int y, int x)
{
	if (y <= 0 || y >= root->y || x <= 0 || x >= root->x)
		return (1);
	if (y == 0 && root->map_int[y][x] == 2)
		return (1);
	if (x == 0 && root->map_int[y][x] == 2)
		return (1);
	if (root->map_int[y][x] == 3)
		return (1);
	return (0);
}

int	change_case(t_mlx *root, int y, int x, int new_case)
{
	int	ret;

	ret = 0;
	if (root->map_int[y][x] == new_case || root->map_int[y][x] == 1)
		return (0);
	else if (check_fail(root, y, x))
		return (1);
	else
	{
		root->map_int[y][x] = new_case;
		ret = change_case(root, y + 1, x, new_case);
		if (ret == 1)
			return (ret);
		ret = change_case(root, y - 1, x, new_case);
		if (ret == 1)
			return (ret);
		ret = change_case(root, y, x + 1, new_case);
		if (ret == 1)
			return (ret);
		ret = change_case(root, y, x - 1, new_case);
		if (ret == 1)
			return (ret);
	}
	return (ret);
}

int	flood_fill(t_mlx *root, int y, int x, int new_case)
{
	if (change_case(root, y, x, new_case))
		return (1);
	return (0);
}
