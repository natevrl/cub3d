# include "../header.h"

static int	isnot_cub(char *str)
{
	size_t	begin;

	begin = ft_strlen(str) - 4;
	if (ft_strncmp(str + begin, ".ber", 4) != 0)
		return (1);
	return (0);
}

int	esc_code(int keycode, t_mlx *vars)
{
	if (keycode == 65307)
		mlx_loop_end(vars->mlx);
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
