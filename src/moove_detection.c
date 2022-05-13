/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_detection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v3r <v3r@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:46:37 by v3r               #+#    #+#             */
/*   Updated: 2022/05/13 18:09:57 by v3r              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	compteur_de_pas(void)
{
	static int	i = 1;

	printf("%d\n", i);
	i++;
}

// int	there_is_wall(t_mlx *root, int x, int y)
// {
// 	int	i;

// 	i = 0;
// 	while (++i < root->walls->max)
// 		if (x == root->walls->x[i] && y == root->walls->y[i])
// 			return (1);
// 	return (0);
// }

