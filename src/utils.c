/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:06:01 by v3r               #+#    #+#             */
/*   Updated: 2022/05/24 13:39:11 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	intstrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_is_num(char *str)
{
	int	i ;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strlen(str + i) > 12)
		return (1);
	if (ft_atoi(str) > INT_MAX)
		return (1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0' && str[i] != '\n')
	{
		return (1);
	}
	return (0);
}

void	return_map_parsing(t_mlx *root, char *all_maps, int fd)
{
	count_elements(root, all_maps);
	if (check_data(root->data_map) != 0)
	{
		free(all_maps);
		data_error(root);
	}
	if (check_map(root, root->map) != 0)
	{
		free(all_maps);
		invalid_map_error(root, NULL);
	}
	free(all_maps);
	close(fd);
}

void	protect_rays_error(t_mlx *root, t_direction *pos)
{
	if ((int)floor(pos->ytocheck / TILE_SIZE) >= root->y)
		pos->ytocheck = (root->y - 1) * 64;
	if ((int)floor(pos->xtocheck / TILE_SIZE) >= root->x)
		pos->xtocheck = (root->x - 1) * 64;
	if ((int)floor(pos->ytocheck / TILE_SIZE) < 0)
		pos->ytocheck = 0;
	if ((int)floor(pos->xtocheck / TILE_SIZE) < 0)
		pos->xtocheck = 0;
}
