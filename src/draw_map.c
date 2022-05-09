/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:44:22 by nbenhado          #+#    #+#             */
/*   Updated: 2022/05/09 18:39:34 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	draw1(t_mlx *root, char *gnl)
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
		else if (gnl[i] == '0')
		{
			if (!(put_ground(root, x, y)))
				return (free_return(gnl));
		}
		x += IMG_BITS;
	}
	y += IMG_BITS;
	return (1);
}

static int	draw2(t_mlx *root, char *gnl)
{
	int			i;
	int			x;
	static int	y = 0;

	i = -1;
	x = 0;
	while (gnl[++i])
	{

		if (gnl[i] == 'P')
		{
			if (!(put_player(root, x, y)))
				return (free_return(gnl));
		}
		x += IMG_BITS;
	}
	y += IMG_BITS;
	return (1);
}


static void	reinit_ground(t_mlx *root)
{
	root->maps->r_path = "./images/center.xpm";
	root->maps->img = mlx_xpm_file_to_image(root->mlx, root->maps->r_path,
			&root->maps->img_width, &root->maps->img_height);
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
		if (!(draw1(root, gnl)) || !(draw2(root, gnl)))
			error++;
		else
			free(gnl);
	}
	reinit_ground(root);
	if (error > 0)
		invalid_map_error(root, 0);
	close(fd);
}
