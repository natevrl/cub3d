/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:27:17 by mderome           #+#    #+#             */
/*   Updated: 2022/06/01 16:59:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	data_error(t_mlx *root)
{
	printf("Error\nData error.\n");
	kill_all(root);
	return (1);
}

int	rgb_error(char **tab)
{
	(void)tab;
	printf("Error\nRGB error.\n");
	return (1);
}

void	check_data_map(t_mlx *root)
{
	int	i;
	int	j;

	i = 0;
	while (root->data_map[i])
	{
		j = ft_strlen(root->data_map[i]) - 2;
		if (root->data_map[i][j] == ' ')
			data_error(root);
		i++;
	}
}
