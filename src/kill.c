/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:49:49 by mderome           #+#    #+#             */
/*   Updated: 2022/05/22 13:59:27 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	kill_window(t_mlx *root)
{
	if (root->mlx)
	{
		if (root->text_up)
			mlx_destroy_image(root->mlx, root->text_up);
		if (root->text_down)
			mlx_destroy_image(root->mlx, root->text_down);
		if (root->text_right)
			mlx_destroy_image(root->mlx, root->text_right);
		if (root->text_left)
			mlx_destroy_image(root->mlx, root->text_left);
		if (root->mlx_win)
			mlx_destroy_window(root->mlx, root->mlx_win);
		if (root->mlx)
			mlx_destroy_display(root->mlx);
	}
}

void	kill_all(t_mlx *root)
{
	kill_window(root);
	if (root->map)
		free_tab(root->map);
	if (root->data_map)
		free_tab(root->data_map);
	free(root->ea);
	free(root->so);
	free(root->no);
	free(root->we);
	if (root->player)
		free(root->player);
	if (root->mlx)
		free(root->mlx);
	if (root)
		free(root);
	exit(0);
}
