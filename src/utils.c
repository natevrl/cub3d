/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:06:01 by v3r               #+#    #+#             */
/*   Updated: 2022/05/22 13:31:39 by mderome          ###   ########.fr       */
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
		data_error(root);
	}
	free(all_maps);
	close(fd);
}
