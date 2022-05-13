/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:41:43 by v3r               #+#    #+#             */
/*   Updated: 2022/05/13 15:07:02 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "libs/minilibx-linux/mlx.h"
# include "libs/get_next_line/get_next_line.h"
# include "libs/libft/libft.h"


# define FALSE 0
# define TRUE 1

# define TILE_SIZE 64
# define NUMBER_MAP_COLS 20
# define NUMBER_MAP_ROWS 13
# define WINDOW_WIDHT (NUMBER_MAP_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (NUMBER_MAP_ROWS * TILE_SIZE)

# define  FOV_ANGLE (60 * PI / 180)
# define NUMS_RAYS WINDOW_WIDTH


# define FPS 30
# define FRAME_TIME_LENGTH (1000 / FPS)
# define PI 3.14159265
# define DOUBLE_PI 6.28318530

// code ascii des touches ZQSD (azerty)
// # define UP 122
// # define DOWN 115
// # define LEFT 113
// # define RIGHT 100

// code ascii des touches WASD (qwerty)
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100

// ascii des fleches du clavier
# define UPA 65362
# define DOWNA 65364
# define LEFTA 65361
# define RIGHTA 65363

typedef struct s_img
{
	void	*img;
	char	*r_path;
	float	width;
	float		height;
	float		x;
	float		y;
	int		starting_position;
	int		turn_direction; // -1 for left, +1 for right
	int		walk_direction; // -1 for back, +1 for front
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_tuple
{
	int	*x;
	int	*y;
	int	max;
	int	touched;
}	t_tuple;

typedef struct s_mlx
{
	int		win_height;
	int		win_width;
	int		is_player;
	char	**data_map;
	char	**map1;
	int		**map;
	int		x; //collone
	int		y; //ligne
	int		pos_p_x;
	int		pos_p_y;
	// int		is_escape;
	void	*mlx;
	void	*mlx_win;
	t_img	*maps;
	t_img	*player;
	t_tuple	*walls;
	// t_tuple	*collectible;
	// t_tuple	*enemies;
}	t_mlx;


// init
void init_img_test(t_mlx *root);
void	game_driver(char *path);
void	kill_all(t_mlx *root);
void	my_mlx_pixel_put(t_mlx *root, int x, int y, int color);

// map & parsing
void	number_of(t_mlx *root, char *str);
void	map_drawer(t_mlx *root, char *str);
void	map_parsing(t_mlx *root, char *path);
void	map_parsing2(t_mlx *root);
int     esc_code(int keycode, t_mlx *root);
int		check_data(char **data);
int		check_map(char **map);
int		flood_fill(t_mlx *root, int y, int x, int new_case);

// player & detections
void	compteur_de_pas(void);
int		is_wall(t_mlx *root, int x, int y);
int		is_escape(t_mlx *root, int x, int y);
void	is_collectible(t_mlx *root, int x, int y);
int		is_enemies(t_mlx *root, int x, int y);
int		moove_player(int keycode, t_mlx *root);
int		stop_player(int keycode, t_mlx *root);
int 	update_image(t_mlx *root);


// put sprites
int		put_wall(t_mlx *root, int x, int y);
int		put_ground(t_mlx *root, int x, int y);
int		put_collectible(t_mlx *root, int x, int y);
int		put_escape(t_mlx *root, int x, int y);
int		put_player(t_mlx *root, int x, int y);
int		put_enemies(t_mlx *root, int x, int y);

//error
void	malloc_error(t_mlx *root);
void	invalid_map_error(t_mlx *root, char *str);
void	check_open_error(t_mlx *root, int fd);
void	check_read_error(t_mlx *root, int ret, char *str);
int		walls_error(t_mlx *root, int line, char *gnl);
int		line_bad_len(t_mlx *root, char *gnl);
int		free_return(char *str);
int		data_error(t_mlx *root);
int		rgb_error(char **tab);

//utils
int		intstrlen(char *str);

//utils_tab
void	free_tab(char **tab);
int		tab_len(char **tab);
void	free_tab_int(int **tab);

void	print_tab(char **tab);

# ifndef BUFF_SIZE
#  define BUFF_SIZE 10
# endif

#endif
