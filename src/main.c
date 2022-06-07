/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:44:19 by mderome           #+#    #+#             */
/*   Updated: 2022/06/07 15:25:27 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	isnot_cub(char *str)
{
	size_t	begin;

	begin = ft_strlen(str) - 4;
	if (ft_strncmp(str + begin, ".cub", 5) != 0 || ft_strlen(str) == 4)
		return (1);
	return (0);
}

int	isnot_xpm(char *str)
{
	size_t	begin;

	begin = ft_strlen(str) - 4;
	if (ft_strncmp(str + begin, ".xpm", 5) != 0 || ft_strlen(str) == 4)
		return (1);
	return (0);
}

void	game_driver2(t_mlx *root)
{
	root->mlx_win = mlx_new_window(root->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	setup_textures(root);
	root->player->rota_angle += (root->player->turn_direction - 0.1)
		* root->player->turn_speed;
	mlx_hook(root->mlx_win, 2, 1L << 0, press_actions, root);
	mlx_hook(root->mlx_win, 3, 1L << 1, release_actions, root);
	mlx_loop_hook(root->mlx, update_image, root);
	mlx_hook(root->mlx_win, 17, 1L << 17, mlx_loop_end, root->mlx);
	mlx_loop(root->mlx);
	kill_all(root);
}

void	game_driver(char *path)
{
	t_mlx	*root;

	root = malloc(sizeof(t_mlx));
	if (root == 0)
		malloc_error(root);
	init_struct(root, path);
	root->mlx = mlx_init();
	init_player(root, 0, 0);
	map_parsing(root, path);
	map_parsing2(root);
	stock_data(root);
	game_driver2(root);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (printf("Error\nInvalid number of arguments\n"), -1);
	if (isnot_cub(av[1]) != 0)
		return (printf("Error\nInvalid map name\n"), -1);
	game_driver(av[1]);
	return (0);
}
