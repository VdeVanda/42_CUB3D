#include "../cub3D.h"

unsigned int get_wall_color(t_game *game, int wall_size, int y_start, int screen_y, int ray_index)
{
    int tex_x;
    int tex_y;
    
    if (!game->tex_wall || !game->tex_wall->adr)
        return (0x808080);
    
    if (wall_size <= 0)
        wall_size = 1;
    
    tex_x = game->tex_float[ray_index] * game->tex_wall->w;
    tex_y = ((screen_y - y_start) * game->tex_wall->h) / wall_size;
    
    //if (tex_x < 0)
    //    tex_x = 0;
    if (tex_x >= game->tex_wall->w)
        tex_x = game->tex_wall->w - 1;
    //if (tex_y < 0)
    //    tex_y = 0;
    if (tex_y >= game->tex_wall->h)
        tex_y = game->tex_wall->h - 1;
    
    return (get_color(game->tex_wall, tex_x, tex_y));
}

void create_strip(t_game *game, int screen_height, int ray_len, int x, int ray_index)
{
    int i;
    
    if (ray_len == 0)
        ray_len = 1;
    int hall_height = (TILE_LEN * screen_height) / ray_len;
    int y_start = (screen_height / 2) - (hall_height / 2);
    int y_end = (screen_height / 2) + (hall_height / 2);
    
    // Draw single column - one ray per screen column for smooth rendering
    i = 0;
    while(i < game->window_h_3d)
    {
        if (i < y_start)
            my_mlx_pixel_put(game->world_3d, x, i, 0x809809);
        else if (i <= y_end && i >= y_start)
            my_mlx_pixel_put(game->world_3d, x, i, get_wall_color(game, hall_height, y_start, i, ray_index));
        else
            my_mlx_pixel_put(game->world_3d, x, i, 0x8B4513);
        i++;
    }
}

void update_strips(t_game *game)
{
    int x = 0;
    
    // One ray per screen column
    while(x < game->window_w_3d)
    {
        create_strip(game, game->window_h_3d, game->rays[x], x, x);
        x++;
    }
}

void render_strips(t_game *game)
{
    update_strips(game);
    mlx_put_image_to_window(game->mlx_3d, game->win_3d, game->world_3d->img, 0, 0);
}