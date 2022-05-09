/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:33:44 by v3r               #+#    #+#             */
/*   Updated: 2022/05/09 16:42:33 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	walls_error(t_mlx *vars, int line, char *gnl)
{
	int	i;

	i = -1;
	if (line == 1 || line == vars->win_height)
	{
		while (gnl[++i] != '\n' && gnl[i])
			if (gnl[i] != '1')
				return (1);
	}
	else if (gnl[0] != '1' || gnl[ft_strlen(gnl) - 2] != '1')
		return (1);
	return (0);
}

int	line_bad_len(t_mlx *vars, char *gnl)
{
	int			len;
	static int	interupt = 1;

	len = intstrlen(gnl);
	if (gnl[len - 1] == '\n')
		len--;
	if (len != vars->win_width && interupt == 1)
		return (1);
	return (0);
}
