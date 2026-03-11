#include "cub3D.h"

void	free_parsing_data(t_game *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(cub->tex_paths[i]);
		i++;
	}
	if (cub->map)
	{
		i = 0;
		while (cub->map[i])
		{
			free(cub->map[i]);
			i++;
		}
		free(cub->map);
	}
}

int main(int argc, char **argv)
{
    t_game *game;

    if (argc != 2)
	{
		parsing_error("Wrong number of arguments");
		return (1);
	}

    printf("1. Initializing structs...\n");
    if (init_structs(&game))
    {
        printf("Error: Init structs failed.\n");
        return (1);
    }

    printf("1.5. Initializing parsing data...\n");
    init_parsing_data(game);

    printf("2. Parsing map file...\n");
    if (!parse_cub_file(game, argv[1]))
	{
		free_parsing_data(game);
		cleanup_game(game);
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
    if (!game->tex_wall[0].img)
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
    game->map = load_maps("./assets/map.cub", count_map_rows("./assets/map.cub"));
    if (!game->map)
    {
        printf("Error: Map failed to load\n");
        cleanup_game(game);
        return (1);
    }

    printf("5.5. Parsing Colors...\n");
    {
        int fd = open("./assets/map.cub", O_RDONLY);
        if (fd >= 0)
        {
            char *line;
            while ((line = get_next_line(fd)))
            {
                if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
                {
                    printf("Found floor line: %s", line);
                    parse_color_line(line, 'F', game);
                }
                else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
                {
                    printf("Found ceiling line: %s", line);
                    parse_color_line(line, 'C', game);
                }
                free(line);
            }
            close(fd);
        }
        printf("Floor color: 0x%06X, Ceiling color: 0x%06X\n", game->floor_color & 0xFFFFFF, game->ceiling_color & 0xFFFFFF);
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
