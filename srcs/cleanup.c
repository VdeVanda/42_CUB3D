#include "../cub3D.h"

void free_map(char **map)
{
    int i;

    if (!map)
        return;
    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void free_texture(t_game *game, t_img *tex)
{
    if (!tex)
        return;
    if (tex->img && game->mlx_3d)
        mlx_destroy_image(game->mlx_3d, tex->img);
    free(tex);
}

void free_textures(t_game *game)
{
    if (game->tex_ceiling)
        free_texture(game, game->tex_ceiling);
    if (game->tex_wall)
        free_texture(game, game->tex_wall);
    if (game->tex_floor)
        free_texture(game, game->tex_floor);
    game->tex_ceiling = NULL;
    game->tex_wall = NULL;
    game->tex_floor = NULL;
}

void free_world(t_game *game)
{
    if (game->world_3d)
    {
        if (game->world_3d->img && game->mlx_3d)
            mlx_destroy_image(game->mlx_3d, game->world_3d->img);
        free(game->world_3d);
        game->world_3d = NULL;
    }
}

void cleanup_game(t_game *game)
{
    if (!game)
        return;
    
    if (game->rays)
    {
        free(game->rays);
        game->rays = NULL;
    }
    
    if (game->tex_float)
    {
        free(game->tex_float);
        game->tex_float = NULL;
    }
    
    free_textures(game);
    free_world(game);
    
    if (game->map)
    {
        free_map(game->map);
        game->map = NULL;
    }
    
    if (game->win_3d && game->mlx_3d)
    {
        mlx_destroy_window(game->mlx_3d, game->win_3d);
        game->win_3d = NULL;
    }
    
    if (game->mlx_3d)
    {
        mlx_destroy_display(game->mlx_3d);
        free(game->mlx_3d);
        game->mlx_3d = NULL;
    }
    
    if (game->player)
    {
        free(game->player);
        game->player = NULL;
    }
    
    free(game);
}

int close_window(t_game *game)
{
    cleanup_game(game);
    exit(0);
    return (0);
}
