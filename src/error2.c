/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:27:17 by mderome           #+#    #+#             */
/*   Updated: 2022/05/12 16:44:39 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	data_error(t_mlx *root)
{
	perror("Error\ndata error");
	kill_all(root);
	return (1);
}

int	rgb_error(char **tab)
{
	perror("Error\nRGB error");
	free_tab(tab);
	return (1);
}