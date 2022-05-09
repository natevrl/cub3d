/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_detection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:46:37 by v3r               #+#    #+#             */
/*   Updated: 2022/05/09 16:42:33 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	compteur_de_pas(void)
{
	static int	i = 1;

	printf("%d\n", i);
	i++;
}

int	is_wall(t_mlx *vars, int x, int y)
{
	int	i;

	i = 0;
	while (++i < vars->walls->max)
		if (x == vars->walls->x[i] && y == vars->walls->y[i])
			return (1);
	return (0);
}

int	is_escape(t_mlx *vars, int x, int y)
{
	if (x == vars->walls->x[0] && y == vars->walls->y[0])
	{
		if (vars->collectible->touched == vars->collectible->max)
			mlx_loop_end(vars->mlx);
		else
			return (1);
	}
	return (0);
}

void	is_collectible(t_mlx *vars, int x, int y)
{
	int	i;

	i = 0;
	while (i < vars->collectible->max)
	{
		if (x == vars->collectible->x[i] && y == vars->collectible->y[i])
		{
			vars->collectible->touched++;
			vars->collectible->x[i] = 0;
			vars->collectible->y[i] = 0;
		}
		i++;
	}
}

int	is_enemies(t_mlx *vars, int x, int y)
{
	int	i;

	i = 0;
	while (i < vars->enemies->max)
	{
		if (x == vars->enemies->x[i] && y == vars->enemies->y[i])
		{
			mlx_destroy_image(vars->mlx, vars->player->img);
			vars->player->r_path = "./images/dead.xpm";
			vars->player->img = mlx_xpm_file_to_image(vars->mlx,
					vars->player->r_path, &vars->player->img_width,
					&vars->player->img_height);
			vars->enemies->touched = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
