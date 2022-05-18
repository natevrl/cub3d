/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:41:43 by v3r               #+#    #+#             */
/*   Updated: 2022/05/18 14:26:20 by mderome          ###   ########.fr       */
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

# define FLT_MAX 3.402823466e+38F
# define TILE_SIZE 64
# define NUMBER_MAP_COLS 20
# define NUMBER_MAP_ROWS 13
# define WINDOW_WIDTH (NUMBER_MAP_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (NUMBER_MAP_ROWS * TILE_SIZE)
// # define WINDOW_WIDTH 1200
// # define WINDOW_HEIGHT 800

# define FOV_ANGLE (60 * PI / 180)
# define NUMBER_OF_RAYS WINDOW_WIDTH


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
	void			*img;
	char			*r_path;
	int				width;
	int				height;
	float			x;
	float			y;
	int				starting_position;
	int				turn_direction; // -1 for left, +1 for right
	int				walk_direction; // -1 for back, +1 for front
	int				orientation;
	float			rotation_angle;
	float			walk_speed;
	float			turn_speed;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				texture_offset_x;
	int				texture_offset_y;
	int				*data_color_addr[4];
}	t_img;

typedef struct s_direction
{
	int found_wall;
	int wall_content;
	float wall_hit_x;
	float wall_hit_y;
	float xintercept;
	float yintercept;
	float next_touch_x;
	float next_touch_y;
	float xstep;
	float ystep;
	int facing_down;
	int facing_up;
	int facing_right;
	int facing_left;
	float hit_distance;
	float x_to_check;
	float y_to_check;
} t_direction;


typedef struct s_project3d
{
	float	perp_distance;
	float	projected_wall_h;
	int		wall_strip_h;
	int		wall_top_pix;
	int		wall_bot_pix;
}		t_project3d;


typedef struct s_rays {
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    int was_hit_vertical;
    int is_ray_facing_up;
    int is_ray_facing_down;
    int is_ray_facing_left;
    int is_ray_facing_right;
    float wall_hit_content;
} t_rays;


typedef struct s_mlx
{
	char	*path;
	char	**data_map;
	char 	**map;
	int		**map_int;
	int		pos_p_y;
	int		pos_p_x;
	int		x;
	int		y;
	int		is_player;
	int		win_height;
	int		win_width;
	int		ceiling;
	int		floor;
	void	*mlx;
	void	*mlx_win;
	t_img	*maps;
	t_img	*player;
	t_rays 	*rays;
	void	*texture_left;
	void	*texture_right;
	void	*texture_up;
	void	*texture_down;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_mlx;


// init
void 	init_img_test(t_mlx *root);
void	game_driver(char *path);
void	kill_all(t_mlx *root);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// map & parsing
void	number_of(t_mlx *root, char *str);
void	map_drawer(t_mlx *root);
void	map_parsing(t_mlx *root, char *str);
int     esc_code(int keycode, t_mlx *root);
char	**fill_map(t_mlx *root);
void	map_parsing2(t_mlx *root);
int		flood_fill(t_mlx *root, int y, int x, int new_case);
int	check_data(char **data);
int    check_map(t_mlx *root, char **map);

// player & detections
int		there_is_wall(t_mlx *root, float x, float y);
void	compteur_de_pas(void);
int		is_escape(t_mlx *root, int x, int y);
void	is_collectible(t_mlx *root, int x, int y);
int		is_enemies(t_mlx *root, int x, int y);
int		press_actions(int keycode, t_mlx *root);
int		release_actions(int keycode, t_mlx *root);
int 	update_image(t_mlx *root);


// put sprites
int		put_wall(t_mlx *root, int x, int y);
int		put_player(t_mlx *root, int x, int y);

//error
void	malloc_error(t_mlx *root);
void	invalid_map_error(t_mlx *root, char *str);
void	check_open_error(t_mlx *root, int fd);
void	check_read_error(t_mlx *root, int ret, char *str);
int		walls_error(t_mlx *root, int line, char *gnl);
int		line_bad_len(t_mlx *root, char *gnl);
int		free_return(char *str);
int		rgb_error(char **tab);
int		data_error(t_mlx *root);

// raycasting
void render_rays(t_mlx *root);
void raycast(t_mlx *root);

//utils
int		intstrlen(char *str);
int		tab_len(char **tab);
void	free_tab(char **tab);
void	free_tab_int(int **tab);


void	generate_3d_projection(t_mlx *root);
void	init_texture(t_mlx *root, t_img *texture);
void	setup_textures(t_mlx *root);

# ifndef BUFF_SIZE
#  define BUFF_SIZE 10
# endif

#endif
