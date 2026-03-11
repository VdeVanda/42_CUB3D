#include "cub3D.h"

int main()
{
    t_game *game;

    printf("1. Initializing structs...\n");
    if (init_structs(&game))
    {
        printf("Error: Init structs failed.\n");
        return (1);
    }
    
    printf("2. Initializing MLXs...\n");
    game->mlx_3d = mlx_init();
    if (!game->mlx_3d)
    {
        printf("Error: MLX init failed.\n");
        cleanup_game(game);
        return(1);
    }

    printf("3. Initializing World...\n");
    init_worlds(game);
    if (!game->world_3d || !game->world_3d->img)
    {
        printf("Error: World init failed.\n");
        cleanup_game(game);
        return(1);
    }

    printf("3.5. Loading Textures...\n");
    init_texs(game);
    if (!game->tex_wall || !game->tex_ceiling || !game->tex_floor)
    {
        printf("Error: Texture loading failed.\n");
        cleanup_game(game);
        return(1);
    }

    printf("4. Creating Window 3D (%d x %d)...\n", game->window_w_3d, game->window_h_3d);
    game->win_3d = mlx_new_window(game->mlx_3d, game->window_w_3d, game->window_h_3d, "3D View");
    if (!game->win_3d)
    {
        printf("Error: Window creation failed.\n");
        cleanup_game(game);
        return(1);
    }
    
    printf("5. Loading Map...\n");
    game->map = load_map("./assets/map.cub", count_map_rows("./assets/map.cub"));
    if (!game->map)
    {
        printf("Error: Map failed to load\n");
        cleanup_game(game);
        return (1);
    }

    create_map(game, count_map_rows("./assets/map.cub"));
    update_rays(game);
    render_strips(game);

    printf("6. Entering Loop (3D window)...\n");
    mlx_hook(game->win_3d, 17, 0, close_window, game);
    mlx_hook(game->win_3d, 2, 1L<<0, key_press, game);
    mlx_hook(game->win_3d, 3, 1L<<1, key_release, game);
    mlx_loop_hook(game->mlx_3d, game_loop, game);
    mlx_loop(game->mlx_3d);
    
    cleanup_game(game);
    return (0);
}
