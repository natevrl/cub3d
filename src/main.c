/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:09:12 by mderome           #+#    #+#             */
/*   Updated: 2022/05/15 15:09:54 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	isnot_cub(char *str)
{
	size_t	begin;

	begin = ft_strlen(str) - 4;
	if (ft_strncmp(str + begin, ".cub", 4) != 0 || begin == 0
		|| str[begin - 1] == '/')
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	*root;

	root = malloc(sizeof(t_mlx));
	if (!root)
		malloc_error(root);
	if (ac != 2)
		return (printf("Error\nInvalid number of arguments\n"), -1);
	if (isnot_cub(av[1]) != 0)
		return (printf("Error\nInvalid map name\n"), -1);
	game_driver(av[1]);
	return (0);
}
