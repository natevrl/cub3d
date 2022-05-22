/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:41:20 by nbenhado          #+#    #+#             */
/*   Updated: 2022/05/22 13:39:06 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	malloc_error(t_mlx *root)
{
	perror("Error\nmalloc() error");
	kill_all(root);
}

void	invalid_map_error(t_mlx *root, char *str)
{
	if (str)
		free(str);
	printf("Error\nInvalid map\n");
	kill_all(root);
}

void	check_open_error(t_mlx *root, int fd)
{
	if (fd == -1)
	{
		perror("Error\nopen() error");
		kill_all(root);
	}
}

void	check_read_error(t_mlx *root, int ret, char *str)
{
	if (ret == -1)
	{
		if (str)
			free(str);
		perror("Error\nread() error");
		kill_all(root);
	}
}

int	free_return(char *str)
{
	free(str);
	return (0);
}
