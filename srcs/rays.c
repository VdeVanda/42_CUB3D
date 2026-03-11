#include "../cub3D.h"

int update_ray(t_game *game, float angle, int x, int y, float *wall_x_text, int *wall_dir)
{
    int max_len = 1000;
    int v_len = 0;
    int new_x;
    int new_y;
    int x_mod;
    int y_mod;
    int dist_west, dist_east, dist_north, dist_south;
    int min_dist;

    while (v_len < max_len)
    {
        new_x = x + (cos(angle) * v_len);
        new_y = y + (sin(angle) * v_len);

        if (game->map[new_y / TILE_LEN][new_x / TILE_LEN] == '1')
        {
            x_mod = new_x % TILE_LEN;
            y_mod = new_y % TILE_LEN;
            if (x_mod < 0) x_mod += TILE_LEN;
            if (y_mod < 0) y_mod += TILE_LEN;

            // Calculate distance to each boundary
            dist_west = x_mod;
            dist_east = TILE_LEN - x_mod;
            dist_north = y_mod;
            dist_south = TILE_LEN - y_mod;

            // Find which boundary is actually closest
            min_dist = dist_west;
            *wall_dir = WALL_WEST;
            *wall_x_text = ((float)y_mod / TILE_LEN);

            if (dist_east < min_dist)
            {
                min_dist = dist_east;
                *wall_dir = WALL_EAST;
                *wall_x_text = ((float)y_mod / TILE_LEN);
            }
            if (dist_north < min_dist)
            {
                min_dist = dist_north;
                *wall_dir = WALL_NORTH;
                *wall_x_text = ((float)x_mod / TILE_LEN);
            }
            if (dist_south < min_dist)
            {
                min_dist = dist_south;
                *wall_dir = WALL_SOUTH;
                *wall_x_text = ((float)x_mod / TILE_LEN);
            }
            return (v_len * cos(angle - game->player->pa));
        }
        v_len++;
    }
    *wall_dir = WALL_NORTH;
    return (v_len * cos(angle - game->player->pa));
}

void update_rays(t_game *game)
{
    int i = 0;
    float la = game->player->fovla;
    float tex_x;
    int wall_dir;
    float angle_step = (2 * FOV) / game->rays_count;

    while (i < game->rays_count)
    {
        game->rays[i] = update_ray(game, la, game->player->px, game->player->py, &tex_x, &wall_dir);
        game->tex_float[i] = tex_x;
        game->wall_direction[i] = wall_dir;
        la += angle_step;
        i++;
    }
}
