#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include "includes/libft/libft.h"
#include "includes/minilibx-linux/mlx.h"
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define TILE_LEN 64

# define RAD 0.017

# define FOV (PI / 4)

# define PI 3.1415926535897932384626433832795

typedef struct s_img
{
    void *img;
    char *adr;
    int bits_per_pixel;
    int line_len;
    int endian;
    int w;
    int h;
}t_img;

typedef struct s_player
{
    float px;
    float py;
    float pa;
    float speed;
    float fovla;
    float fovra;
}t_player;

typedef struct s_game
{
    void *mlx_2d;
    void *win_2d;
    void *mlx_3d;
    void *win_3d;
    t_img *world_2d;
    t_img *world_3d;
    t_img *tex_wall;
    t_img *tex_floor;
    t_img *tex_ceiling;
    char **map;
    float *rays;
    float *tex_float;
    int rays_count;
    t_player *player;
    int window_w_3d;
    int window_h_3d;
    int window_w;
    int window_h;
    int key_w;
    int key_a;
    int key_s;
    int key_d;
    int key_left;
    int key_right;
}t_game;

/* srcs/walls.c*/
unsigned int get_wall_color(t_game *game, int wall_size, int y_start, int screen_y, int ray_index);
void create_strip(t_game *game, int screen_height, int ray_len, int x, int ray_index);
void render_strips(t_game *game);

/* srcs/create.c */
unsigned int get_color(t_img *img, int x, int y);
void    create_map(t_game *game, int height);
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
void    add_cube(t_img *img, int width, int height, int x, int y, int color);

/* srcs/init.c */
void init_texs(t_game *game);
void    init_worlds(t_game *game);
int init_structs(t_game **game);

/* srcs/map.c */
int     count_map_col(char *file);
int		count_map_rows(char *file);
char	**load_map(char *file, int height);
void	print_map(t_game *game, int height);
void	render_map(t_game *game);

/* srcs/player.c */
void	check_player(t_game *game, int x, int y);

/* srcs/rays.c*/
void update_rays(t_game *game);
void render_rays(t_game *game, int color);

/* srcs/move.c*/
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
int game_loop(t_game *game);

/* srcs/cleanup.c */
void free_map(char **map);
void free_texture(t_game *game, t_img *tex);
void free_textures(t_game *game);
void free_world(t_game *game);
void cleanup_game(t_game *game);
int close_window(t_game *game);

#endif
