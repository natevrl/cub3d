/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_detection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:46:37 by v3r               #+#    #+#             */
/*   Updated: 2022/05/09 18:17:36 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	compteur_de_pas(void)
{
	static int	i = 1;

	printf("%d\n", i);
	i++;
}

int	is_wall(t_mlx *root, int x, int y)
{
	int	i;

	i = 0;
	while (++i < root->walls->max)
		if (x == root->walls->x[i] && y == root->walls->y[i])
			return (1);
	return (0);
}