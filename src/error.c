#include "../header.h"

void	malloc_error(t_mlx *vars)
{
	perror("Error\nmalloc() error");
	kill_all(vars);
}

void	invalid_map_error(t_mlx *vars, char *str)
{
	if (str)
		free(str);
	printf("Error\nInvalid map\n");
	kill_all(vars);
}

void	check_open_error(t_mlx *vars, int fd)
{
	if (fd == -1)
	{
		perror("Error\nopen() error");
		kill_all(vars);
	}
}

void	check_read_error(t_mlx *vars, int ret, char *str)
{
	if (ret == -1)
	{
		if (str)
			free(str);
		perror("Error\nread() error");
		kill_all(vars);
	}
}

int	free_return(char *str)
{
	free(str);
	return (0);
}
