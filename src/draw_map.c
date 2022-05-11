/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v3r <v3r@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:44:22 by nbenhado          #+#    #+#             */
/*   Updated: 2022/05/11 22:12:12 by v3r              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"



static int	draw(t_mlx *root, char *gnl)
{
	int			i;
	int			x;
	static int	y = 0;

	i = -1;
	x = 0;
	while (gnl[++i])
	{
		
		if (gnl[i] == '1')
		{
			if (!(put_wall(root, x, y)))
				return (free_return(gnl));
		}
		// if (gnl[i] == 'P')
		// {
		// 	if (!(put_player(root, x, y)))
		// 		return (free_return(gnl));
		// printf("YuP\n");
		// }
		x += TILE_SIZE;
	}
	y += TILE_SIZE;
	return (1);
}


void	map_drawer(t_mlx *root, char *str)
{
	int		fd;
	char	*gnl;
	int		line;
	int		error;

	fd = open(str, O_RDONLY);
	check_open_error(root, fd);
	line = 0;
	error = 0;
	while (1)
	{
		gnl = get_next_line(fd);
		if (!gnl)
			break ;
		if (line_bad_len(root, gnl) || walls_error(root, ++line, gnl))
			error++;
		if (!(draw(root, gnl)))
			error++;
		else
			free(gnl);
	}
	if (error > 0)
		invalid_map_error(root, 0);
	close(fd);
}
