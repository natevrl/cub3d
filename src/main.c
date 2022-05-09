# include "../header.h"

// static int	isnot_ber(char *str)
// {
// 	size_t	begin;

// 	begin = ft_strlen(str) - 4;
// 	if (ft_strncmp(str + begin, ".ber", 4) != 0)
// 		return (1);
// 	return (0);
// }

int	esc_code(int keycode, t_mlx *vars)
{
	if (keycode == 65307)
		mlx_loop_end(vars->mlx);
	return (0);
}


int	main(void)
{
    t_mlx	*root;

	root = malloc(sizeof(t_mlx));
	if (!root)
		malloc_error(root);
	// if (ac != 2)
	// 	return (printf("Error\nInvalid number of arguments\n"), -1);
	// if (isnot_ber(av[1]) != 0)
	// 	return (printf("Error\nInvalid map name\n"), -1);
	// game_driver(av[1]);
    root->mlx = mlx_init();
	root->mlx_win = mlx_new_window(root->mlx, 1000, 1000, "cub3D");
	mlx_hook(root->mlx_win, 17, 1L << 17, mlx_loop_end, root->mlx);
	mlx_hook(root->mlx_win, 2, 1L << 0, esc_code, root);
	mlx_loop(root->mlx);

	return (0);
}
