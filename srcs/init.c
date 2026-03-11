#include "../cub3D.h"

float *init_rays(t_game *game, int nbr)
{
    int i = 0;
    float *rays = malloc(sizeof(float) * nbr);
    if (!rays)
        return(NULL);
    while (i < nbr)
    {
        rays[i] = 0;
        i++;
    }
    game->rays_count = i;
    printf("%d \n",game->rays_count);
    return(rays);
}

int init_structs(t_game **game)
{
    *game = (t_game *)malloc(sizeof(t_game));
    if (!*game)
        return (1);

    (*game)->player = (t_player *)malloc(sizeof(t_player));
    if (!(*game)->player)
    {
        free(*game);
        return (1);
    }
    (*game)->rays_count = 0;
    (*game)->mlx_3d = NULL;
    (*game)->win_3d = NULL;
    (*game)->world_3d = NULL;
    (*game)->tex_ceiling = NULL;
    (*game)->tex_wall = NULL;
    (*game)->tex_floor = NULL;
    (*game)->map = NULL;

    int cols = count_map_col("./assets/map.cub");
    int rows = count_map_rows("./assets/map.cub");
    printf("DEBUG: cols=%d, rows=%d\n", cols, rows);
    (*game)->window_w_3d = 1500;
    (*game)->window_h_3d = 1000;
    (*game)->key_w = 0;
    (*game)->key_a = 0;
    (*game)->key_s = 0;
    (*game)->key_d = 0;
    (*game)->key_left = 0;
    (*game)->key_right = 0;

    (*game)->rays = init_rays(*game, (*game)->window_w_3d);
    if (!(*game)->rays)
    {
        free((*game)->player);
        free(*game);
        return (1);
    }
    (*game)->tex_float = init_rays(*game, (*game)->window_w_3d);
    if (!(*game)->tex_float)
    {
        free((*game)->rays);
        free((*game)->player);
        free(*game);
        return (1);
    }
    (*game)->window_w = cols * TILE_LEN;
    (*game)->window_h = rows * TILE_LEN;

    return (0);
}

void init_texs(t_game *game)
{
    game->tex_ceiling = (t_img *)malloc(sizeof(t_img));
    game->tex_wall = (t_img *)malloc(sizeof(t_img));
    game->tex_floor = (t_img *)malloc(sizeof(t_img));

    if (!game->tex_floor || !game->tex_ceiling || !game->tex_wall)
    {
        if (game->tex_ceiling)
            free(game->tex_ceiling);
        if (game->tex_wall)
            free(game->tex_wall);
        if (game->tex_floor)
            free(game->tex_floor);
        game->tex_ceiling = NULL;
        game->tex_wall = NULL;
        game->tex_floor = NULL;
        return ;
    }
    game->tex_ceiling->img = mlx_xpm_file_to_image(game->mlx_3d, "./assets/ceiling.xpm", &game->tex_ceiling->w, &game->tex_ceiling->h);
    game->tex_wall->img = mlx_xpm_file_to_image(game->mlx_3d, "./assets/wall_1.xpm", &game->tex_wall->w, &game->tex_wall->h);
    game->tex_floor->img = mlx_xpm_file_to_image(game->mlx_3d, "./assets/floor.xpm", &game->tex_floor->w, &game->tex_floor->h);

    if (!game->tex_floor->img || !game->tex_ceiling->img || !game->tex_wall->img)
    {
        free_textures(game);
        return ;
    }
    game->tex_ceiling->adr = mlx_get_data_addr(game->tex_ceiling->img, &game->tex_ceiling->bits_per_pixel, &game->tex_ceiling->line_len, &game->tex_ceiling->endian);
    game->tex_wall->adr = mlx_get_data_addr(game->tex_wall->img, &game->tex_wall->bits_per_pixel, &game->tex_wall->line_len, &game->tex_wall->endian);
    game->tex_floor->adr = mlx_get_data_addr(game->tex_floor->img, &game->tex_floor->bits_per_pixel, &game->tex_floor->line_len, &game->tex_floor->endian);
}

void init_worlds(t_game *game)
{
    game->world_3d = (t_img *)malloc(sizeof(t_img));
    if (!game->world_3d)
        return;

    game->world_3d->img = mlx_new_image(game->mlx_3d, game->window_w_3d, game->window_h_3d);
    if (!game->world_3d->img)
    {
        free(game->world_3d);
        game->world_3d = NULL;
        return;
    }

    game->world_3d->adr = mlx_get_data_addr(game->world_3d->img, &game->world_3d->bits_per_pixel, &game->world_3d->line_len, &game->world_3d->endian);
    if (!game->world_3d->adr)
    {
        mlx_destroy_image(game->mlx_3d, game->world_3d->img);
        free(game->world_3d);
        game->world_3d = NULL;
        return;
    }
    game->world_3d->w = game->window_w_3d;
    game->world_3d->h = game->window_h_3d;
}
