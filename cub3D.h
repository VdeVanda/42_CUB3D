/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:01:10 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/25 17:57:31 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "includes/libft/libft.h"
# include "includes/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/* TEXTURE SIDES */
# define TEX_N 0
# define TEX_E 1
# define TEX_S 2
# define TEX_W 3

/* WALL DIRECTIONS */
# define WALL_NORTH 0
# define WALL_EAST 1
# define WALL_SOUTH 2
# define WALL_WEST 3

/* KEYCODES */
# define KEY_UP 65362
# define KEY_W 119
# define KEY_LEFT 65361
# define KEY_A 97
# define KEY_DOWN 65364
# define KEY_S 115
# define KEY_RIGHT 65363
# define KEY_D 100
# define KEY_ESC 65307

# define TILE_LEN 64

# define RAD 0.017
# define PI 3.1415926535897932384626433832795
# define FOV 0.785398163397448309615660845819875721

typedef struct s_img
{
	void		*img;
	char		*adr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}				t_img;

typedef struct s_player
{
	float		px;
	float		py;
	float		pa;
	float		speed;
	float		fovla;
	float		fovra;
}				t_player;

typedef struct s_ray
{
	float		dist;
	float		tex_x;
	int			wall_dir;
}				t_ray;

typedef struct s_game
{
	void		*mlx_3d;
	void		*win_3d;
	t_img		*world_3d;
	t_img		tex_wall[4];
	char		*tex_paths[4];
	char		**map;
	t_ray		*rays;
	int			rays_count;
	t_player	*player;
	int			map_rows;
	int			map_cols;
	char		player_start_dir;
	int			player_start_col;
	int			player_start_row;
	int			floor_color;
	int			ceiling_color;
	int			window_w_3d;
	int			window_h_3d;
	int			window_w;
	int			window_h;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
}				t_game;

/* srcs/walls.c*/
unsigned int	get_wall_color(t_game *game, int params[3], int ray_idx);
void			create_strip(t_game *game, int x);
void			render_strips(t_game *game);

/* srcs/create.c */
unsigned int	get_color(t_img *img, int x, int y);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				load_textures(t_game *cub);

/* srcs/init.c */
void			init_texs(t_game *game);
void			init_worlds(t_game *game);
int				init_structs(t_game **game);

/* srcs/player.c */
void			init_player_from_start(t_game *game);

/* srcs/ray_cast.c */
void			update_rays(t_game *game);

/* srcs/move.c*/
int				game_loop(t_game *game);

/* srcs/input.c*/
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

/* srcs/cleanup.c */
void			free_map(char **map);
void			free_textures(t_game *game);
void			cleanup_game(t_game *game);
int				close_window(t_game *game);

/* *************** PARSING *************** */

/* srcs/parsing/check_map.c */
int				validate_map(t_game *cub);

/* srcs/parsing/map_loading.c */
int				count_map_dimensions(t_game *cub, int fd);
int				load_map(t_game *cub, char *filename);

/* srcs/parsing/parse_colors.c */
int				parse_color_line(char *line, char type, t_game *cub);

/* srcs/parsing/parse_header.c */
int				parse_header(t_game *cub, int fd);

/* srcs/parsing/parse_main.c */
void			init_parsing_data(t_game *cub);
int				parse_cub_file(t_game *cub, char *filename);

/* srcs/parsing/parse_utils.c */
void			parsing_error(char *message);
void			free_str_arr(char **arr);
char			*ft_strtrim_nl(char *str);
char			*pad_line(char *line, int width);

void			free_parsing_data(t_game *cub);

#endif
