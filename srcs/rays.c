#include "../cub3D.h"

int update_ray(t_game *game, float angle, int x, int y, float *wall_x_text)
{
    int max_len = 1000;
    int v_len = 0;
    int new_x;
    int new_y;  
    
    while (v_len < max_len)
    {
        new_x = x + (cos(angle) * v_len);
        new_y = y + (sin(angle) * v_len);

        if (game->map[new_y /TILE_LEN][new_x / TILE_LEN] == '1')
        {
            float tex_x = ((float)new_x / TILE_LEN) - floor(new_x / TILE_LEN);
            float tex_y = ((float)new_y / TILE_LEN) - floor(new_y / TILE_LEN);
            if (new_x % TILE_LEN <= 1 || new_x % TILE_LEN >= TILE_LEN - 1)
                *wall_x_text = tex_y;
            else
                *wall_x_text = tex_x;
            return(v_len * cos(angle - game->player->pa));
        }
        v_len++;
    }
    return(v_len * cos(angle - game->player->pa));
}

void update_rays(t_game *game)
{
    int i = 0;
    float la = game->player->fovla;
    float tex_x;
    float angle_step = (2 * FOV) / game->rays_count;
    
    while (i < game->rays_count)
    {
        game->rays[i] = update_ray(game, la, game->player->px, game->player->py, &tex_x);
        game->tex_float[i] = tex_x;
        la += angle_step;
        i++;
    }
}