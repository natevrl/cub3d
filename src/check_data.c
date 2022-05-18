/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:33:35 by mderome           #+#    #+#             */
/*   Updated: 2022/05/17 14:05:12 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	check_wall(char *info)
{
	char	**data;
	int		fd;

	data = ft_split(info, '\n');
	fd = open(data[0], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		printf("Error\nFile %s : not found\n", data[0]);
		free_tab(data);
		return (1);
	}
	free_tab(data);
	close(fd);
	return (0);
}

static int	check_cf(char *info, char **tab)
{
	char	**data;
	int		i;

	i = 0;
	data = ft_split(info + 2, ',');
	if (tab_len(data) != 3)
	{
		free_tab(data);
		return (rgb_error(tab));
	}
	while (data && data[i])
	{
		if (ft_atoi(data[i]) < 0 || ft_atoi(data[i]) > 255)
		{
			free_tab(data);
			return (rgb_error(tab));
		}
		i++;
	}
	free_tab(data);
	return (0);
}

int	check_data(char **data)
{
	char	**info;
	int		i;

	i = -1;
	if (!data)
		return (1);
	info = ft_split(data[0], ' ');
	while (data[++i])
	{
		if (ftstrlen(info[0]) == 2)
		{
			if (check_wall(info[1]) != 0)
				return (free_tab(info), 0);
		}
		else if (ftstrlen(info[0]) == 1)
		{
			if (check_cf(info[1], info) != 0)
				return (free_tab(info), 0);
		}
		else
			return (free_tab(info), 1);
		free_tab(info);
		info = ft_split(data[i], ' ');
	}
	return (free_tab(info), 0);
}

int    parse_color(char *path)
{
    int		r;
    int		g;
    int		b;
    int		converted_color;
    char	**color;

    color = ft_split(path, ',');
    r = ft_atoi(color[0]);
    g = ft_atoi(color[1]);
    b = ft_atoi(color[2]);
	free_tab(color);
    converted_color = r << 16 | g << 8 | b;
    return (converted_color);
}

void	stock_data(t_mlx *root)
{
	root->ceiling = parse_color(root->data_map[5]);
	root->floor = parse_color(root->data_map[4]);
}
