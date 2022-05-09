/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:44:22 by nbenhado          #+#    #+#             */
/*   Updated: 2022/05/09 16:42:33 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	draw1(t_mlx *vars, char *gnl)
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
			if (!(put_wall(vars, x, y)))
				return (free_return(gnl));
		}
		else if (gnl[i] == '0')
		{
			if (!(put_ground(vars, x, y)))
				return (free_return(gnl));
		}
		x += IMG_BITS;
	}
	y += IMG_BITS;
	return (1);
}

static int	draw2(t_mlx *vars, char *gnl)
{
	int			i;
	int			x;
	static int	y = 0;

	i = -1;
	x = 0;
	while (gnl[++i])
	{
		if (gnl[i] == 'E')
		{
			if (!(put_escape(vars, x, y)))
				return (free_return(gnl));
		}
		else if (gnl[i] == 'P')
		{
			if (!(put_player(vars, x, y)))
				return (free_return(gnl));
		}
		x += IMG_BITS;
	}
	y += IMG_BITS;
	return (1);
}

static int	draw3(t_mlx *vars, char *gnl)
{
	int			i;
	int			x;
	static int	y = 0;

	i = -1;
	x = 0;
	while (gnl[++i])
	{
		if (gnl[i] == 'N')
		{
			if (!(put_enemies(vars, x, y)))
				return (free_return(gnl));
		}
		else if (gnl[i] == 'C')
		{
			if (!(put_collectible(vars, x, y)))
				return (free_return(gnl));
		}
		x += IMG_BITS;
	}
	y += IMG_BITS;
	return (1);
}

static void	reinit_ground(t_mlx *vars)
{
	vars->maps->r_path = "./images/center.xpm";
	vars->maps->img = mlx_xpm_file_to_image(vars->mlx, vars->maps->r_path,
			&vars->maps->img_width, &vars->maps->img_height);
}

void	map_drawer(t_mlx *vars, char *str)
{
	int		fd;
	char	*gnl;
	int		line;
	int		error;

	fd = open(str, O_RDONLY);
	check_open_error(vars, fd);
	line = 0;
	error = 0;
	while (1)
	{
		gnl = get_next_line(fd);
		if (!gnl)
			break ;
		if (line_bad_len(vars, gnl) || walls_error(vars, ++line, gnl))
			error++;
		if (!(draw1(vars, gnl)) || !(draw2(vars, gnl)) || !(draw3(vars, gnl)))
			error++;
		else
			free(gnl);
	}
	reinit_ground(vars);
	if (error > 0)
		invalid_map_error(vars, 0);
	close(fd);
}
