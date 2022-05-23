/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:27:17 by mderome           #+#    #+#             */
/*   Updated: 2022/05/23 15:42:19 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	data_error(t_mlx *root)
{
	perror("Error\nData error");
	kill_all(root);
	return (1);
}

int	rgb_error(char **tab)
{
	(void)tab;
	perror("Error\nRGB error");
	return (1);
}

void	check_data_map(t_mlx *root)
{
	int	i;
	int	j;

	i = 0;
	while (root->data_map[i])
	{
		j = 3;
		while (root->data_map[i][j])
		{
			if (root->data_map[i][j] == ' ' || root->data_map[i][j] == '\t')
				data_error(root);
			j++;
		}
		i++;
	}
}
