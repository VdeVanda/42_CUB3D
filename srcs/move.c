#include "../cub3D.h"

void move_front(t_game *game)
{
    float x = cos(game->player->pa) * game->player->speed * 13;
    float y = sin(game->player->pa) * game->player->speed * 13;

    int tile_x = (int)(game->player->px + x) / TILE_LEN;
    int tile_y = (int)(game->player->py + y) / TILE_LEN;

    if (tile_x < 0 || tile_y < 0 || !game->map[tile_y] || tile_x >= (int)strlen(game->map[tile_y]))
    {
        return;
    }
    if (game->map[tile_y][tile_x] == '1')
    {
        return;
    }
    update_rays(game);
    game->player->px += x;
    game->player->py += y;
    update_rays(game);
    render_strips(game);
}

void move_back(t_game *game)
{
    float x = cos(game->player->pa) * game->player->speed * 13;
    float y = sin(game->player->pa) * game->player->speed * 13;

    int tile_x = (int)(game->player->px - x) / TILE_LEN;
    int tile_y = (int)(game->player->py - y) / TILE_LEN;

    if (tile_x < 0 || tile_y < 0 || !game->map[tile_y] || tile_x >= (int)strlen(game->map[tile_y]))
    {
        return;
    }
    if (game->map[tile_y][tile_x] == '1')
    {
        return;
    }
    update_rays(game);
    game->player->px -= x;
    game->player->py -= y;
    update_rays(game);
    render_strips(game);
}

void rotate_left(t_game *game)
{
    update_rays(game);
    game->player->pa -= game->player->speed / 2;
    game->player->fovra = game->player->pa + FOV;
    game->player->fovla = game->player->pa - FOV;
    update_rays(game);
    render_strips(game);
}

void rotate_right(t_game *game)
{
    update_rays(game);
    game->player->pa += game->player->speed / 2;
    game->player->fovra = game->player->pa + FOV;
    game->player->fovla = game->player->pa - FOV;
    update_rays(game);
    render_strips(game);
}

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->key_w = 1;
    if (keycode == KEY_A)
        game->key_a = 1;
    if (keycode == KEY_S)
        game->key_s = 1;
    if (keycode == KEY_D)
        game->key_d = 1;
    if (keycode == 65361)
        game->key_left = 1;
    if (keycode == 65363)
        game->key_right = 1;
    if (keycode == KEY_ESC)
        close_window(game);
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->key_w = 0;
    if (keycode == KEY_A)
        game->key_a = 0;
    if (keycode == KEY_S)
        game->key_s = 0;
    if (keycode == KEY_D)
        game->key_d = 0;
    if (keycode == 65361)
        game->key_left = 0;
    if (keycode == 65363)
        game->key_right = 0;
    return (0);
}

int game_loop(t_game *game)
{
    game->player->speed = 0.25;
    if (game->key_w)
        move_front(game);
    if (game->key_a)
        rotate_left(game);
    if (game->key_s)
        move_back(game);
    if (game->key_d)
        rotate_right(game);
    if (game->key_left)
        rotate_left(game);
    if (game->key_right)
        rotate_right(game);
    return (0);
}
