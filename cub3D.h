#ifndef CUB3D_H
# define CUB3D_H

# include "includes/libft/libft.h"
# include "includes/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

// TEXTURE SIDES
# define TEX_N 0
# define TEX_E 1
# define TEX_S 2
# define TEX_W 3

// WALL DIRECTIONS
# define WALL_NORTH 0
# define WALL_EAST 1
# define WALL_SOUTH 2
# define WALL_WEST 3

// KEYCODES
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
//# define HEIGHT 1000
//# define WIDTH 1500

# define RAD 0.017

# define FOV (PI / 4)

# define PI 3.1415926535897932384626433832795

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

typedef struct s_game
{
	void		*mlx_3d;
	void		*win_3d;
	t_img		*world_3d;
	t_img		tex_wall[4];
	char		*tex_paths[4];
	int			*wall_direction;
	char		**map;
	float		*rays;
	float		*tex_float;
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
unsigned int	get_wall_color(t_game *game, int wall_size, int y_start,
					int screen_y, int ray_index);
void			create_strip(t_game *game, int screen_height, int ray_len,
					int x, int ray_index);
void			render_strips(t_game *game);

/* srcs/create.c */
unsigned int	get_color(t_img *img, int x, int y);
void			create_map(t_game *game, int height);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			add_cube(t_img *img, int width, int height, int x, int y,
					int color);
int				load_textures(t_game *cub);

/* srcs/init.c */
void			init_texs(t_game *game);
void			init_worlds(t_game *game);
int				init_structs(t_game **game);

/* srcs/map.c */
int				count_map_col(char *file);
int				count_map_rows(char *file);
char			**load_maps(char *file, int height);
void			print_map(t_game *game, int height);
void			render_map(t_game *game);

/* srcs/player.c */
void			check_player(t_game *game, int x, int y);

/* srcs/rays.c*/
void			update_rays(t_game *game);
void			render_rays(t_game *game, int color);

/* srcs/move.c*/
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				game_loop(t_game *game);

/* srcs/cleanup.c */
void			free_map(char **map);
void			free_texture(t_game *game, t_img *tex);
void			free_textures(t_game *game);
void			free_world(t_game *game);
void			cleanup_game(t_game *game);
int				close_window(t_game *game);

// *************** PARSING ***************

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
int				main(int argc, char **argv);

#endif
